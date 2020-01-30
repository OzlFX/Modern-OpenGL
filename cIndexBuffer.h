#ifndef _CINDEXBUFFER_H_
#define _CINDEXBUFFER_H_

#include <GL/glew.h>

class cIndexBuffer
{
private:

	GLuint m_ID;
	GLuint m_Count;

public:

	cIndexBuffer(const unsigned int* _data, GLuint _count);
	~cIndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline GLuint getCount() const { return m_Count; }

};

#endif