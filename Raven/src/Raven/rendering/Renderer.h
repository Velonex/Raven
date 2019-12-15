#pragma once

#include "RenderCommand.h"

#include "OrthographicCamera.h"
#include "Shader.h"
#include <glm.hpp>
#include <Raven/core/Core.h>

namespace rvn {

	class Renderer {
	public:
		static void init();
		static void shutdown();

		static void beginScene(OrthographicCamera& camera); // TODO: Take in scene attribs
		static void endScene();

		static void submit(const ref<Shader>& shader, const ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API getApi() { return RendererAPI::getAPI(); }

		static void onWindowResize(uint32_t width, uint32_t height);
	private:
		struct SceneData {
			glm::mat4 _viewProjectionMatrix;
		};
		static scope<SceneData> s_sceneData;
	};
}