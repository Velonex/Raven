#include "Renderer.h"
#include <NightFall/platform/opengl/OpenGLRenderer.h>
#include <NightFall/utils/Assert.h>
#include <glad/glad.h>


namespace nfe {
	Renderer::SceneData* Renderer::s_sceneData = new SceneData;
	void Renderer::beginScene(OrthographicCamera& camera)
	{
		s_sceneData->_viewProjectionMatrix = camera.getViewProjectionMatrix();
	}
	void Renderer::endScene()
	{
	}
	void Renderer::submit(const Shader* shader, const VertexArray* vertexArray)
	{
		shader->bind();
		vertexArray->bind();
		shader->uploadUniformMat4("u_viewProjection", s_sceneData->_viewProjectionMatrix);
		RenderCommand::drawIndexed(vertexArray);
	}
}