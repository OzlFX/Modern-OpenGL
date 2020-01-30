#ifndef _CUTIL_H_
#define _CUTIL_H_

#include <string>
#include <GL/glew.h>

#define TRY(x) GLClearError();\
	x;\
	GLCheckError(__FILE__, __LINE__)

void GLClearError();

void GLCheckError(const char* _file, int _line);

struct sException : public std::exception
{
	const char* what(std::string _msg) const { return _msg.c_str(); }
};

#endif