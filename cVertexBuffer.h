#ifndef _CVERTEXBUFFER_H_
#define _CVERTEXBUFFER_H_

#include <GL/glew.h>

class cVertexBuffer
{
private:

	GLuint m_ID;

public:

	cVertexBuffer(const void* _data, GLuint _size);
	~cVertexBuffer();

	void Bind() const;
	void Unbind() const;

};

#endif