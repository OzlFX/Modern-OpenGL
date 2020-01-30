#include "cIndexBuffer.h"
#include "cUtil.h"

cIndexBuffer::cIndexBuffer(const GLuint* _data, GLuint _count)
	: m_Count(_count)
{
	glGenBuffers(1, &m_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
	TRY(glBufferData(GL_ELEMENT_ARRAY_BUFFER, _count * sizeof(_count), _data, GL_STATIC_DRAW));
}

void cIndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void cIndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

cIndexBuffer::~cIndexBuffer()
{
	glDeleteBuffers(1, &m_ID);
}