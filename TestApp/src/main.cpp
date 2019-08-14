#include <NightFall.h>
#include <imgui.h>

class TestApp : public nfe::NightFallApplication {
};

TestApp app;

class TestLayer : public nfe::Layer {
public:
	TestLayer() {

	}
	virtual void onAttach() override {
		_camera = new nfe::OrthographicCamera(-1.6f, 1.6f, -.9f, .9f);

		{
			_vertexArray = nfe::VertexArray::create();

			float vertices[3 * 7] = {
				-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
				 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
				 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
			};

			_vertexBuffer = nfe::VertexBuffer::create(vertices, sizeof(vertices));

			nfe::BufferLayout layout = {
				{ nfe::ShaderDataType::Float3, "a_Position" },
				{ nfe::ShaderDataType::Float4, "a_Color" }
			};
			_vertexBuffer->setLayout(layout);

			_vertexArray->addVertexBuffer(_vertexBuffer);

			unsigned int indices[3] = {
				0, 1, 2
			};

			_indexBuffer = nfe::IndexBuffer::create(indices, sizeof(indices));

			_vertexArray->setIndexBuffer(_indexBuffer);

			std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_viewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main() {
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_viewProjection * vec4(a_Position, 1.0);
			}
			)";
			std::string pixelSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main() {
				color = v_Color;
			}
			)";
			_shader = new nfe::Shader(vertexSrc, pixelSrc);
		}
		{
			_vertexArraysq = nfe::VertexArray::create();

			float vertices[3 * 4] = {
				-0.75f, -0.75f, 0.0f,
				 0.75f, -0.75f, 0.0f,
				 0.75f,  0.75f, 0.0f,
				-0.75f,  0.75f, 0.0f
			};


			_vertexBuffersq = nfe::VertexBuffer::create(vertices, sizeof(vertices));

			nfe::BufferLayout layout = {
				{ nfe::ShaderDataType::Float3, "a_Position" }
			};
			_vertexBuffersq->setLayout(layout);

			_vertexArraysq->addVertexBuffer(_vertexBuffersq);

			uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };

			_indexBuffersq = nfe::IndexBuffer::create(indices, sizeof(indices));

			_vertexArraysq->setIndexBuffer(_indexBuffersq);

			std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_viewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_viewProjection * vec4(a_Position, 1.0);
			}
			)";
			std::string pixelSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(0.2, 0.8, 0.3, 1.0);
			}
			)";
			_shadersq = new nfe::Shader(vertexSrc, pixelSrc);
		}
	}
	virtual void onImGuiRender() override {
		ImGui::Begin("TestWindow");
		ImGui::Text("Test");
		ImGui::End();
	}
	virtual void onUpdate(nfe::Timestep ts) override {
		_camera->setRotation(45.f);

		LOG_TRACE("Last frame time: {}", ts.getSeconds());

		nfe::Renderer::beginScene(*_camera);
		{
			nfe::Renderer::submit(_shadersq, _vertexArraysq);
			nfe::Renderer::submit(_shader, _vertexArray);
		}
		nfe::Renderer::endScene();
	}
	virtual void onEvent(nfe::Event* e) override {
		switch (e->getType()) {
			case nfe::EventType::EVENT_KEY_PRESSED: {
				nfe::KeyPressedEvent* ev = (nfe::KeyPressedEvent*) e;
				switch (ev->getKeyCode()) {
				case KEY_A: {
					const glm::vec3& pos = _camera->getPosition();
					_camera->setPosition({ pos.x - 0.05f, pos.y, pos.z });
					break;
				}
				case KEY_D: {
					const glm::vec3& pos = _camera->getPosition();
					_camera->setPosition({ pos.x + 0.05f, pos.y, pos.z });
					break;
				}
				case KEY_W: {
					const glm::vec3& pos = _camera->getPosition();
					_camera->setPosition({ pos.x, pos.y + 0.05f, pos.z });
					break;
				}
				case KEY_S: {
					const glm::vec3& pos = _camera->getPosition();
					_camera->setPosition({ pos.x, pos.y - 0.05f, pos.z });
					break;
				}
				default:
					break;
				}
			}
		}
	}
	private:
	// Rendering
	nfe::VertexArray* _vertexArray;
	nfe::VertexBuffer* _vertexBuffer;
	nfe::IndexBuffer* _indexBuffer;
	nfe::Shader* _shader;

	// Rendering 2
	nfe::VertexArray* _vertexArraysq;
	nfe::VertexBuffer* _vertexBuffersq;
	nfe::IndexBuffer* _indexBuffersq;
	nfe::Shader* _shadersq;

	nfe::OrthographicCamera* _camera;
};

int main() {
	app.setInstance(&app);
	app.init((char*)"TestApp");
	TestLayer* lyr = new TestLayer();
	app.getLayerStack()->pushOverlay(lyr);
	app.run();
	return app.quit();
}