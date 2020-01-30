#ifndef _CVERTEXARRAY_H_
#define _CVERTEXARRAY_H_

#include <memory>
#include <GL/glew.h>

class cVertexBuffer;
class cVertexBufferLayout;

class cVertexArray
{
private:

	GLuint m_ID;

public:

	cVertexArray();

	void AddBuffer(const std::shared_ptr<cVertexBuffer> _buffer, const std::shared_ptr<cVertexBufferLayout> _layout);

	void Bind() const;
	void Unbind() const;

	~cVertexArray();

};

#endif