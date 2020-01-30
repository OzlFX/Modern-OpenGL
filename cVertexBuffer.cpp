#include "cVertexBuffer.h"
#include "cUtil.h"

cVertexBuffer::cVertexBuffer(const void * _data, GLuint _size)
{
	glGenBuffers(1, &m_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	TRY(glBufferData(GL_ARRAY_BUFFER, _size, _data, GL_STATIC_DRAW));
}

void cVertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void cVertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

cVertexBuffer::~cVertexBuffer()
{
	glDeleteBuffers(1, &m_ID);
}