#pragma once

#include "RenderCommand.h"

#include "Camera.h"
#include "Shader.h"
#include <glm.hpp>
#include <NightFall/core/Core.h>

namespace nfe {

	class Renderer {
	public:
		static void beginScene(OrthographicCamera& camera); // TODO: Take in scene attribs
		static void endScene();

		static void submit(const ref<Shader>& shader, const ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API getApi() { return RendererAPI::getAPI(); }
	private:
		struct SceneData {
			glm::mat4 _viewProjectionMatrix;
		};
		static SceneData* s_sceneData;
	};
}