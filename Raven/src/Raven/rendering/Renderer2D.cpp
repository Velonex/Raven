#include <pch.h>
#include "Renderer2D.h"
#include <Raven/rendering/VertexArray.h>
#include <Raven/rendering/Shader.h>
#include <Raven/rendering/RenderCommand.h>
#include <gtc/matrix_transform.hpp>

namespace rvn {

	struct RenderStorage {
		ref<VertexArray> quadVertexArray;
		ref<Shader> textureShader;
		ref<Texture2D> whiteTexture;
	};

	static RenderStorage* s_data;

	void Renderer2D::init()
	{
		RVN_PROFILE_FUNCTION();
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

		s_data->whiteTexture = Texture2D::create(1, 1);
		uint32_t texData = 0xFFFFFFFF;
		s_data->whiteTexture->setData(&texData, 4);

		s_data->textureShader = Shader::create("assets/shaders/texture.glsl");
		s_data->textureShader->bind();
		s_data->textureShader->setInt("u_Texture", 0);
	}
	void Renderer2D::shutdown()
	{
		RVN_PROFILE_FUNCTION();
		delete s_data;
	}
	void Renderer2D::beginScene(const OrthographicCamera& camera)
	{
		RVN_PROFILE_FUNCTION();
		s_data->textureShader->bind();
		s_data->textureShader->setMat4("u_ViewProjection", camera.getViewProjectionMatrix());
	}
	void Renderer2D::endScene()
	{
		RVN_PROFILE_FUNCTION();
	}
	void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		drawQuad({ position.x, position.y, 0.0f }, size, color);
	}
	void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		RVN_PROFILE_FUNCTION();
		s_data->textureShader->setFloat4("u_Color", color);
		s_data->whiteTexture->bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_data->textureShader->setMat4("u_Transform", transform);

		s_data->quadVertexArray->bind();
		RenderCommand::drawIndexed(s_data->quadVertexArray);
	}
	void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const ref<Texture2D>& texture)
	{
		drawQuad({ position.x, position.y, 0.0f }, size, texture);
	}
	void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const ref<Texture2D>& texture)
	{
		RVN_PROFILE_FUNCTION();
		s_data->textureShader->setFloat4("u_Color", glm::vec4(1.0f));
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_data->textureShader->setMat4("u_Transform", transform);

		texture->bind();

		s_data->quadVertexArray->bind();
		RenderCommand::drawIndexed(s_data->quadVertexArray);
	}
	void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2 & size, const ref<Texture2D>& texture, const glm::vec4 & color)
	{
		drawQuad({ position.x, position.y, 0.0f }, size, texture, color);
	}
	void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2 & size, const ref<Texture2D>& texture, const glm::vec4 & color)
	{
		RVN_PROFILE_FUNCTION();
		s_data->textureShader->setFloat4("u_Color", color);
		s_data->whiteTexture->bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_data->textureShader->setMat4("u_Transform", transform);

		texture->bind();

		s_data->quadVertexArray->bind();
		RenderCommand::drawIndexed(s_data->quadVertexArray);
	}
}