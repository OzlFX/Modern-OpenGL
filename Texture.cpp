#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

cTexture::cTexture(const std::string& _path)
	: m_ID(0), m_FilePath(_path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(_path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	glGenTextures(1, &m_ID);

	if (!m_ID) throw std::exception();

	glBindTexture(GL_TEXTURE_2D, m_ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	stbi_image_free(m_LocalBuffer);
}

void cTexture::Bind(unsigned int _slot) const
{
	glActiveTexture(GL_TEXTURE0 + _slot);
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

void cTexture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

cTexture::~cTexture()
{
	glDeleteTextures(1, &m_ID);
}
