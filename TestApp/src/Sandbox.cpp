#include "Sandbox.h"
#include <imgui.h>
#include <gtc/matrix_transform.hpp>
#include <Raven/platform/opengl/OpenGLShader.h>
#include <Raven/core/Core.h>
#include <stb_image.h>

void Sandbox::onAttach() {
		_cameraController = rvn::createRef<rvn::OrthographicCameraController>(1280.0f / 720.0f, true);
		_squarePos = glm::vec3(0.0f);
		_vertexArraysq = rvn::VertexArray::create();

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
			{ rvn::ShaderDataType::Float2, "v_TexCoord" }
		};
		sqVB->setLayout(layout);

		_vertexArraysq->addVertexBuffer(sqVB);

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
		ref<rvn::IndexBuffer> sqIB;
		sqIB.reset(rvn::IndexBuffer::create(indices, sizeof(indices)));

		_vertexArraysq->setIndexBuffer(sqIB);

		ref<rvn::Shader> s = _shaderLib.load("assets/shaders/texture.glsl");

		_texsq = rvn::Texture2D::create("assets/textures/chess.png");
		_texsq2 = rvn::Texture2D::create("assets/textures/blend.png");

		std::dynamic_pointer_cast<rvn::OpenGLShader>(s)->bind();
		std::dynamic_pointer_cast<rvn::OpenGLShader>(s)->uploadUniformInt("u_Texture", 0);
}

void Sandbox::onUpdate(rvn::Timestep ts) {
	_cameraController->onUpdate(ts);

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), _squarePos);

	rvn::Renderer::beginScene(_cameraController->getCamera());
	{
		auto textureShader = _shaderLib.get("texture");
		_texsq->bind();
		rvn::Renderer::submit(textureShader, _vertexArraysq, transform);
		_texsq2->bind();
		rvn::Renderer::submit(textureShader, _vertexArraysq);
	}
	rvn::Renderer::endScene();
}
