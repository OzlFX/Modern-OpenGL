#include "ShaderProgram.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/ext.hpp>

cShaderProgram::cShaderProgram(const std::string & _file)
	: m_FilePath(_file), m_ID(0)
{
	sShaderSource source = Load(_file);
	m_ID = CreateShader(source.m_VertexSrc, source.m_FragmentSrc);
}

GLint cShaderProgram::getUniformLocation(const std::string & _name)
{
	if (m_UniformLocationCache.find(_name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[_name];

	GLint loc = glGetUniformLocation(m_ID, _name.c_str());

	if (loc == -1)
		std::cout << "Warning: uniform '" << _name << "' does not exist!" << std::endl;
	else
		m_UniformLocationCache[_name] = loc;

	return loc;
}

GLuint cShaderProgram::CreateShader(const std::string& _vert, const std::string& _frag)
{
	GLuint ID = glCreateProgram();
	GLuint vert = CompileShader(GL_VERTEX_SHADER, _vert);
	GLuint frag = CompileShader(GL_FRAGMENT_SHADER, _frag);

	glAttachShader(ID, vert);
	glAttachShader(ID, frag);

	glLinkProgram(ID);
	glValidateProgram(ID);

	glDeleteShader(vert);
	glDeleteShader(frag);

	return ID;
}

sShaderSource cShaderProgram::Load(const std::string& _file)
{
	std::ifstream file(_file);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(file, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				//Add to the vertex
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				//Add to the fragment
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

GLuint cShaderProgram::CompileShader(GLuint _type, const std::string& _src)
{
	GLuint ID = glCreateShader(_type);
	const char* src = _src.c_str();
	glShaderSource(ID, 1, &src, nullptr);
	glCompileShader(ID);

	int success;
	glGetShaderiv(ID, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		int length;
		glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &length);
		char* error = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(ID, length, &length, error);

#ifdef _DEBUG
		std::cout << "Failed to compile " <<
			(_type == GL_VERTEX_SHADER ? "Vertex" : "Fragment")
			<< std::endl;
#endif
		glDeleteShader(ID);
		return 0;
	}

	return ID;
}

void cShaderProgram::Bind() const
{
	glUseProgram(m_ID);
}

void cShaderProgram::Unbind() const
{
	glUseProgram(0);
}

void cShaderProgram::setUniform(const std::string & _name, glm::vec4 _value)
{
	glUniform4f(getUniformLocation(_name), _value.x, _value.y, _value.z, _value.w);
}

void cShaderProgram::setUniform(const std::string & _name, glm::mat4 _value)
{
	glUniformMatrix4fv(getUniformLocation(_name), 1, GL_FALSE, glm::value_ptr(_value));
}

void cShaderProgram::setUniform(const std::string & _name, int _value)
{
	glUniform1i(getUniformLocation(_name), _value);
}

cShaderProgram::~cShaderProgram()
{
	glDeleteProgram(m_ID);
}
