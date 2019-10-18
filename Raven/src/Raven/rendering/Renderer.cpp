#include "Renderer.h"
#include <Raven/platform/opengl/OpenGLRenderer.h>
#include <Raven/platform/opengl/OpenGLShader.h>
#include <Raven/utils/Assert.h>
#include <glad/glad.h>


namespace rvn {
	scope<Renderer::SceneData> Renderer::s_sceneData = createScope<SceneData>();
	void Renderer::beginScene(OrthographicCamera& camera)
	{
		s_sceneData->_viewProjectionMatrix = camera.getViewProjectionMatrix();
	}
	void Renderer::endScene()
	{
	}
	void Renderer::submit(const ref<Shader>& shader, const ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->bind();
		vertexArray->bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uploadUniformMat4("u_viewProjection", s_sceneData->_viewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uploadUniformMat4("u_transform", transform);
		RenderCommand::drawIndexed(vertexArray);
	}
	void Renderer::onWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::setViewport(0, 0, width, height);
	}
	void Renderer::init() {
		RenderCommand::init();
	}
}