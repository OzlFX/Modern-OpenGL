#ifndef _CRENDERER_H_
#define _CRENDERER_H_

#include <memory>

class cVertexArray;
class cIndexBuffer;
class cShaderProgram;

class cRenderer
{
private:



public:

	void Draw(const std::shared_ptr<cVertexArray> _mesh, const std::shared_ptr<cIndexBuffer> _indexbuffer, 
		const std::shared_ptr<cShaderProgram> _shader) const;

	void Clear() const;

	~cRenderer();
};

#endif