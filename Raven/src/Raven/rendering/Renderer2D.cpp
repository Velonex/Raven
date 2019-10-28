#include "Renderer2D.h"
#include <Raven/rendering/VertexArray.h>
#include <Raven/rendering/Shader.h>
#include <Raven/rendering/RenderCommand.h>


namespace rvn {

	struct RenderStorage {
		ref<VertexArray> quadVertexArray;
		ref<Shader> flatColorShader;
	};

	static RenderStorage* s_data;

	void Renderer2D::init()
	{
		s_data = new RenderStorage();
		s_data->quadVertexArray = rvn::VertexArray::create();

		float vertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		ref<rvn::VertexBuffer> sqVB;
		sqVB.reset(rvn::VertexBuffer::create(vertices, sizeof(vertices)));

		rvn::BufferLayout layout = {
			{ rvn::ShaderDataType::Float3, "a_Position" }
		};
		sqVB->setLayout(layout);

		s_data->quadVertexArray->addVertexBuffer(sqVB);

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
		ref<rvn::IndexBuffer> sqIB;
		sqIB.reset(rvn::IndexBuffer::create(indices, sizeof(indices)));

		s_data->quadVertexArray->setIndexBuffer(sqIB);

		s_data->flatColorShader = Shader::create("assets/shaders/flatColorShader.glsl");
	}
	void Renderer2D::shutdown()
	{
		delete s_data;
	}
	void Renderer2D::beginScene(const OrthographicCamera& camera)
	{
		s_data->flatColorShader->bind();
		s_data->flatColorShader->setMat4("u_viewProjection", camera.getViewProjectionMatrix());
		s_data->flatColorShader->setMat4("u_transform", glm::mat4(1.0f));
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
		s_data->flatColorShader->setFloat4("u_color", color);

		s_data->quadVertexArray->bind();
		RenderCommand::drawIndexed(s_data->quadVertexArray);
	}
}