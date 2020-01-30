#ifndef _CTEXTURE_H_
#define _CTEXTURE_H_

#include <GL/glew.h>
#include <string>

class cTexture
{
private:

	GLuint m_ID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;

public:

	cTexture(const std::string& _path);

	void Bind(unsigned int _slot = 0) const;
	void Unbind() const;

	inline int getWidth() const { return m_Width; }
	inline int getHeight() const { return m_Height; }

	~cTexture();

};

#endif