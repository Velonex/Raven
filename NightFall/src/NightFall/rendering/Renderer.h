#pragma once

#include "RenderCommand.h"

#include "Camera.h"
#include "Shader.h"

namespace nfe {

	class Renderer {
	public:
		static void beginScene(OrthographicCamera& camera); // TODO: Take in scene attribs
		static void endScene();

		static void submit(const Shader* shader, const VertexArray* vertexArray);

		inline static RendererAPI::API getApi() { return RendererAPI::getAPI(); }
	private:
		struct SceneData {
			glm::mat4 _viewProjectionMatrix;
		};
		static SceneData* s_sceneData;
	};
}