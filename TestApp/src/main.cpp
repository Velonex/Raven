#include <NightFall.h>
#include <imgui.h>
#include <NightFall/application/Input.h>
#include <gtc/matrix_transform.hpp>
#include <NightFall/platform/opengl/OpenGLShader.h>
#include <NightFall/core/Core.h>
#include <stb_image.h>

#include <glad/glad.h>

class TestApp : public nfe::NightFallApplication {
};

TestApp app;

class TestLayer : public nfe::Layer {
public:
	TestLayer() {

	}
	virtual void onAttach() override {
		_camera.reset(new nfe::OrthographicCamera(-1.6f, 1.6f, -.9f, .9f));
		_squarePos = glm::vec3(0.0f);
		//{
		//
		//	_vertexArray.reset(nfe::VertexArray::create());
		//
		//	float vertices[3 * 7] = {
		//		-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
		//		 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
		//		 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		//	};
		//
		//	_vertexBuffer.reset(nfe::VertexBuffer::create(vertices, sizeof(vertices)));
		//
		//	nfe::BufferLayout layout = {
		//		{ nfe::ShaderDataType::Float3, "a_Position" },
		//		{ nfe::ShaderDataType::Float4, "a_Color" }
		//	};
		//	_vertexBuffer->setLayout(layout);
		//
		//	_vertexArray->addVertexBuffer(_vertexBuffer);
		//
		//	unsigned int indices[3] = {
		//		0, 1, 2
		//	};
		//	
		//	_indexBuffer.reset(nfe::IndexBuffer::create(indices, sizeof(indices)));
		//
		//	_vertexArray->setIndexBuffer(_indexBuffer);
		//
		//	std::string vertexSrc = R"(
		//	#version 330 core
		//
		//	layout(location = 0) in vec3 a_Position;
		//	layout(location = 1) in vec4 a_Color;
		//
		//	uniform mat4 u_viewProjection;
		//	uniform mat4 u_transform;
		//
		//	out vec3 v_Position;
		//	out vec4 v_Color;
		//
		//	void main() {
		//		v_Position = a_Position;
		//		v_Color = a_Color;
		//		gl_Position = u_viewProjection * u_transform * vec4(a_Position, 1.0);
		//	}
		//	)";
		//	std::string pixelSrc = R"(
		//	#version 330 core
		//
		//	layout(location = 0) out vec4 color;
		//
		//	in vec3 v_Position;
		//	in vec4 v_Color;
		//
		//	void main() {
		//		color = v_Color;
		//	}
		//	)";
		//	_shader.reset(nfe::Shader::create(vertexSrc, pixelSrc));
		//}
		{
			_vertexArraysq.reset(nfe::VertexArray::create());

			float vertices[5 * 4] = {
				-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
				 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
				 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
				-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
			};


			_vertexBuffersq.reset(nfe::VertexBuffer::create(vertices, sizeof(vertices)));

			nfe::BufferLayout layout = {
				{ nfe::ShaderDataType::Float3, "a_Position" },
				{ nfe::ShaderDataType::Float2, "v_TexCoord" }
			};
			_vertexBuffersq->setLayout(layout);

			_vertexArraysq->addVertexBuffer(_vertexBuffersq);

			uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };

			_indexBuffersq.reset(nfe::IndexBuffer::create(indices, sizeof(indices)));

			_vertexArraysq->setIndexBuffer(_indexBuffersq);

			std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_viewProjection;
			uniform mat4 u_transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_viewProjection * u_transform * vec4(a_Position, 1.0);
			}
			)";
			std::string pixelSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
			)";

			ref<nfe::Shader> s = nfe::Shader::create(vertexSrc, pixelSrc);

			_shaderLib.add("texture", s);

			_texsq = nfe::Texture2D::create("assets/textures/chess.png");
			_texsq2 = nfe::Texture2D::create("assets/textures/blend.png");

			std::dynamic_pointer_cast<nfe::OpenGLShader>(s)->bind();
			std::dynamic_pointer_cast<nfe::OpenGLShader>(s)->uploadUniformInt("u_Texture", 0);

		}
	}
	virtual void onUpdate(nfe::Timestep ts) override {

		if (nfe::Input::isKeyPressed(KEY_A)) {
			_squarePos.x -= ts * 0.5f;
		}
		if (nfe::Input::isKeyPressed(KEY_D)) {
			_squarePos.x += ts * 0.5f;
		}
		if (nfe::Input::isKeyPressed(KEY_W)) {
			_squarePos.y += ts * 0.5f;
		}
		if (nfe::Input::isKeyPressed(KEY_S)) {
			_squarePos.y -= ts * 0.5f;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), _squarePos);

		nfe::Renderer::beginScene(*_camera);
		{
			auto textureShader = _shaderLib.get("texture");
			_texsq->bind();
			nfe::Renderer::submit(textureShader, _vertexArraysq, transform);
			_texsq2->bind();
			nfe::Renderer::submit(textureShader, _vertexArraysq);
		}
		nfe::Renderer::endScene();
	}
	private:
	// Rendering Square
	ref<nfe::VertexArray> _vertexArraysq;
	ref<nfe::VertexBuffer> _vertexBuffersq;
	ref<nfe::IndexBuffer> _indexBuffersq;
	ref<nfe::Texture2D> _texsq;
	ref<nfe::Texture2D> _texsq2;
	glm::vec3 _squarePos;

	nfe::ShaderLibrary _shaderLib;
	ref<nfe::OrthographicCamera> _camera;
};

int main() {
	app.setInstance(&app);
	app.init((char*)"TestApp");
	TestLayer* lyr = new TestLayer();
	app.getLayerStack()->pushOverlay(lyr);
	app.run();
	return app.quit();
}