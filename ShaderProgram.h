#ifndef _CSHADERPROGRAM_H_
#define _CSHADERPROGRAM_H_

#include <string>
#include <GL/glew.h>
#include <unordered_map>
#include <glm/glm.hpp>

struct sShaderSource
{
	std::string m_VertexSrc;
	std::string m_FragmentSrc;
};

class cShaderProgram
{
private:

	GLuint m_ID;
	std::unordered_map<std::string, GLint> m_UniformLocationCache;
	std::string m_FilePath;

	GLint getUniformLocation(const std::string& _name);
	GLuint CreateShader(const std::string& _vert, const std::string& _frag);
	GLuint CompileShader(GLuint _type, const std::string& _src);
	sShaderSource Load(const std::string& _file);

public:

	cShaderProgram(const std::string& _file);

	void Bind() const;
	void Unbind() const;

	//Set uniforms
	void setUniform(const std::string& _name, glm::vec4 _value);
	void setUniform(const std::string& _name, glm::mat4 _value);
	void setUniform(const std::string& _name, int _value);

	~cShaderProgram();

};

#endif