#include "cUtil.h"
#include <iostream>

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

void GLCheckError(const char* _file, int _line)
{
	sException e;

	while (GLenum error = glGetError())
	{
		std::string msg = "OpenGL Error: " + error;
		msg += " in file: " + (std::string)_file + " at line: " + std::to_string(_line);

#ifdef _DEBUG
		std::cout << msg << std::endl;
#endif

		throw e.what(msg);
	}
}