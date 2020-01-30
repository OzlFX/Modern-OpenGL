#include "cRenderer.h"
#include "VertexArray.h"
#include "cIndexBuffer.h"
#include "ShaderProgram.h"
#include "cUtil.h"

void cRenderer::Draw(const std::shared_ptr<cVertexArray> _mesh, const std::shared_ptr<cIndexBuffer> _indexbuffer, const std::shared_ptr<cShaderProgram> _shader) const
{
	_shader->Bind();
	_mesh->Bind();
	_indexbuffer->Bind();

	TRY(glDrawElements(GL_TRIANGLES, _indexbuffer->getCount(), GL_UNSIGNED_INT, nullptr));
}

void cRenderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}

cRenderer::~cRenderer()
{
}