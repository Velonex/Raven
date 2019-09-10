#pragma once

#include "RenderCommand.h"

#include "Camera.h"
#include "Shader.h"
#include <glm.hpp>

namespace nfe {

	class Renderer {
	public:
		static void beginScene(OrthographicCamera& camera); // TODO: Take in scene attribs
		static void endScene();

		static void submit(const Shader* shader, const VertexArray* vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API getApi() { return RendererAPI::getAPI(); }
	private:
		struct SceneData {
			glm::mat4 _viewProjectionMatrix;
		};
		static SceneData* s_sceneData;
	};
}