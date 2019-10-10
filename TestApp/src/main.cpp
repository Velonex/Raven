#include <Raven.h>
#include <imgui.h>
#include <Raven/application/Input.h>
#include <gtc/matrix_transform.hpp>
#include <Raven/platform/opengl/OpenGLShader.h>
#include <Raven/core/Core.h>
#include <stb_image.h>

#include <glad/glad.h>

class TestApp : public rvn::Application {
};

TestApp app;

class TestLayer : public rvn::Layer {
public:
	TestLayer() {

	}
	virtual void onAttach() override {
		_camera.reset(new rvn::OrthographicCamera(-1.6f, 1.6f, -.9f, .9f));
		_squarePos = glm::vec3(0.0f);
		_vertexArraysq.reset(rvn::VertexArray::create());

		float vertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};


		_vertexBuffersq.reset(rvn::VertexBuffer::create(vertices, sizeof(vertices)));

		rvn::BufferLayout layout = {
			{ rvn::ShaderDataType::Float3, "a_Position" },
			{ rvn::ShaderDataType::Float2, "v_TexCoord" }
		};
		_vertexBuffersq->setLayout(layout);

		_vertexArraysq->addVertexBuffer(_vertexBuffersq);

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };

		_indexBuffersq.reset(rvn::IndexBuffer::create(indices, sizeof(indices)));

		_vertexArraysq->setIndexBuffer(_indexBuffersq);

		ref<rvn::Shader> s = _shaderLib.load("assets/shaders/texture.glsl");

		_texsq = rvn::Texture2D::create("assets/textures/chess.png");
		_texsq2 = rvn::Texture2D::create("assets/textures/blend.png");

		std::dynamic_pointer_cast<rvn::OpenGLShader>(s)->bind();
		std::dynamic_pointer_cast<rvn::OpenGLShader>(s)->uploadUniformInt("u_Texture", 0);
	}
	virtual void onUpdate(rvn::Timestep ts) override {

		if (rvn::Input::isKeyPressed(KEY_A)) {
			_squarePos.x -= ts * 0.5f;
		}
		if (rvn::Input::isKeyPressed(KEY_D)) {
			_squarePos.x += ts * 0.5f;
		}
		if (rvn::Input::isKeyPressed(KEY_W)) {
			_squarePos.y += ts * 0.5f;
		}
		if (rvn::Input::isKeyPressed(KEY_S)) {
			_squarePos.y -= ts * 0.5f;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), _squarePos);

		rvn::Renderer::beginScene(*_camera);
		{
			auto textureShader = _shaderLib.get("texture");
			_texsq->bind();
			rvn::Renderer::submit(textureShader, _vertexArraysq, transform);
			_texsq2->bind();
			rvn::Renderer::submit(textureShader, _vertexArraysq);
		}
		rvn::Renderer::endScene();
	}
	private:
	// Rendering Square
	ref<rvn::VertexArray> _vertexArraysq;
	ref<rvn::VertexBuffer> _vertexBuffersq;
	ref<rvn::IndexBuffer> _indexBuffersq;
	ref<rvn::Texture2D> _texsq;
	ref<rvn::Texture2D> _texsq2;
	glm::vec3 _squarePos;

	rvn::ShaderLibrary _shaderLib;
	ref<rvn::OrthographicCamera> _camera;
};

int main() {
	app.setInstance(&app);
	app.init((char*)"TestApp");
	TestLayer* lyr = new TestLayer();
	app.getLayerStack()->pushOverlay(lyr);
	app.run();
	return app.quit();
}