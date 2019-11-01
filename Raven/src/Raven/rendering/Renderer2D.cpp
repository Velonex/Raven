#include "Renderer2D.h"
#include <Raven/rendering/VertexArray.h>
#include <Raven/rendering/Shader.h>
#include <Raven/rendering/RenderCommand.h>
#include <gtc/matrix_transform.hpp>

namespace rvn {

	struct RenderStorage {
		ref<VertexArray> quadVertexArray;
		ref<Shader> flatColorShader;
		ref<Shader> textureShader;
	};

	static RenderStorage* s_data;

	void Renderer2D::init()
	{
		s_data = new RenderStorage();
		s_data->quadVertexArray = rvn::VertexArray::create();

		float vertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		ref<rvn::VertexBuffer> sqVB;
		sqVB.reset(rvn::VertexBuffer::create(vertices, sizeof(vertices)));

		rvn::BufferLayout layout = {
			{ rvn::ShaderDataType::Float3, "a_Position" },
			{ rvn::ShaderDataType::Float2, "a_TexCoord" }
		};
		sqVB->setLayout(layout);

		s_data->quadVertexArray->addVertexBuffer(sqVB);

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
		ref<rvn::IndexBuffer> sqIB;
		sqIB.reset(rvn::IndexBuffer::create(indices, sizeof(indices)));

		s_data->quadVertexArray->setIndexBuffer(sqIB);

		s_data->flatColorShader = Shader::create("assets/shaders/flatColorShader.glsl");
		s_data->textureShader = Shader::create("assets/shaders/texture.glsl");
		s_data->textureShader->bind();
		s_data->textureShader->setInt("u_Texture", 0);
	}
	void Renderer2D::shutdown()
	{
		delete s_data;
	}
	void Renderer2D::beginScene(const OrthographicCamera& camera)
	{
		s_data->flatColorShader->bind();
		s_data->flatColorShader->setMat4("u_ViewProjection", camera.getViewProjectionMatrix());
		s_data->textureShader->bind();
		s_data->textureShader->setMat4("u_ViewProjection", camera.getViewProjectionMatrix());
	}
	void Renderer2D::endScene()
	{
	}
	void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		drawQuad({ position.x, position.y, 0.0f }, size, color);
	}
	void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		s_data->flatColorShader->bind();
		s_data->flatColorShader->setFloat4("u_Color", color);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_data->flatColorShader->setMat4("u_Transform", transform);

		s_data->quadVertexArray->bind();
		RenderCommand::drawIndexed(s_data->quadVertexArray);
	}
	void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const ref<Texture2D>& texture)
	{
		drawQuad({ position.x, position.y, 0.0f }, size, texture);
	}
	void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const ref<Texture2D>& texture)
	{
		s_data->textureShader->bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_data->textureShader->setMat4("u_Transform", transform);

		texture->bind();

		s_data->quadVertexArray->bind();
		RenderCommand::drawIndexed(s_data->quadVertexArray);
	}
}