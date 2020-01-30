#include "VertexArray.h"
#include "cVertexBuffer.h"
#include "VertexBufferLayout.h"

cVertexArray::cVertexArray()
{
	glGenVertexArrays(1, &m_ID);
	glBindVertexArray(m_ID);
}

void cVertexArray::AddBuffer(const std::shared_ptr<cVertexBuffer> _buffer, const std::shared_ptr<cVertexBufferLayout> _layout)
{
	Bind();
	_buffer->Bind();
	const auto& elements = _layout->getElements();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element->m_Count, element->m_Type, 
			element->m_Normalised , _layout->getStride(), (const void*) offset);
		offset += element->m_Count * sVertexBufferElement::getTypeSize(element->m_Type);
	}
}

void cVertexArray::Bind() const
{
	glBindVertexArray(m_ID);
}

void cVertexArray::Unbind() const
{
	glBindVertexArray(0);
}

cVertexArray::~cVertexArray()
{
	glDeleteVertexArrays(1, &m_ID);
}
