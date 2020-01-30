#ifndef _CVERTEXBUFFERLAYOUT_H_
#define _CVERTEXBUFFERLAYOUT_H_

#include <memory>
#include <vector>
#include <GL/glew.h>

struct sVertexBufferElement
{
	sVertexBufferElement(GLuint _type, GLuint _count, unsigned char _normalised)
	{
		m_Type = _type;
		m_Count = _count;
		m_Normalised = _normalised;
	}

	GLuint m_Count;
	GLuint m_Type;
	unsigned char m_Normalised;

	static GLuint getTypeSize(GLuint _type)
	{
		switch (_type)
		{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		}
		return 0;
	}
};

class cVertexBufferLayout
{
private:

	std::vector<std::shared_ptr<sVertexBufferElement>> m_Elements;
	unsigned int m_Stride = 0;

public:

	template <typename T>
	void Push(GLuint _count)
	{
		static_assert(false);
	}

	template <>
	void Push<float>(GLuint _count)
	{
		m_Elements.push_back(std::make_shared<sVertexBufferElement>(GL_FLOAT, _count, GL_FALSE));
		m_Stride += _count * sVertexBufferElement::getTypeSize(GL_FLOAT);
	}

	template <>
	void Push<GLuint>(GLuint _count)
	{
		m_Elements.push_back(std::make_shared<sVertexBufferElement>(GL_UNSIGNED_INT, _count, GL_FALSE));
		m_Stride += _count * sVertexBufferElement::getTypeSize(GL_UNSIGNED_INT);
	}

	template <>
	void Push<unsigned char>(GLuint _count)
	{
		m_Elements.push_back(std::make_shared<sVertexBufferElement>(GL_UNSIGNED_BYTE, _count, GL_TRUE));
		m_Stride += _count * sVertexBufferElement::getTypeSize(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<std::shared_ptr<sVertexBufferElement>> getElements() const { return m_Elements; }
	inline unsigned int getStride() const { return m_Stride; }

};

#endif