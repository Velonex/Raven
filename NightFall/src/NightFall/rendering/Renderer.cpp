#include "Renderer.h"
#include <NightFall/platform/opengl/OpenGLRenderer.h>
#include <NightFall/platform/opengl/OpenGLShader.h>
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
	void Renderer::submit(const Shader* shader, const VertexArray* vertexArray, const glm::mat4& transform)
	{
		shader->bind();
		vertexArray->bind();
		((OpenGLShader*)shader)->uploadUniformMat4("u_viewProjection", s_sceneData->_viewProjectionMatrix);
		((OpenGLShader*)shader)->uploadUniformMat4("u_transform", transform);
		RenderCommand::drawIndexed(vertexArray);
	}
}