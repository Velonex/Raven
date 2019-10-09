#include "Renderer.h"
#include <NightFall/platform/opengl/OpenGLRenderer.h>
#include <NightFall/platform/opengl/OpenGLShader.h>
#include <NightFall/utils/Assert.h>
#include <glad/glad.h>


namespace nfe {
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
	void Renderer::init() {
		RenderCommand::init();
	}
}