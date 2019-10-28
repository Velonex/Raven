#include "Sandbox2D.h"
#include <imgui.h>
#include <gtc/matrix_transform.hpp>
#include <Raven/platform/opengl/OpenGLShader.h>
#include <Raven/core/Core.h>
#include <stb_image.h>

void Sandbox2D::onAttach() {
	_cameraController = rvn::createRef<rvn::OrthographicCameraController>(1280.0f / 720.0f, true);
	_squarePos = glm::vec3(0.0f);
	_vertexArraysq = rvn::VertexArray::create();

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

	_vertexArraysq->addVertexBuffer(sqVB);

	uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
	ref<rvn::IndexBuffer> sqIB;
	sqIB.reset(rvn::IndexBuffer::create(indices, sizeof(indices)));

	_vertexArraysq->setIndexBuffer(sqIB);

	_shaderLib.load("assets/shaders/flatColorShader.glsl");
}

void Sandbox2D::onUpdate(rvn::Timestep ts) {
	_cameraController->onUpdate(ts);

	rvn::Renderer::beginScene(_cameraController->getCamera());
	{
		auto flatColorShader = _shaderLib.get("flatColorShader");
		flatColorShader->bind();
		flatColorShader->setFloat4("u_color", { 0.9f, 0.2f, 0.67f, 1.0f });
		rvn::Renderer::submit(flatColorShader, _vertexArraysq);
	}
	rvn::Renderer::endScene();
}
