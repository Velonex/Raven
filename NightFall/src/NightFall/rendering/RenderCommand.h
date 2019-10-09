#pragma once

#include "RendererAPI.h"

namespace nfe {

	class RenderCommand
	{
	public:
		inline static void drawIndexed(const ref<VertexArray> vertexArray) {
			s_api->drawIndexed(vertexArray);
		}

		inline static void setClearColor(const glm::vec4& color) {
			s_api->setClearColorRGBA(color);
		}
		inline static void clear() {
			s_api->clear();
		}
		inline static void init() {
			s_api->init();
		}
	private:
		static scope<RendererAPI> s_api;
	};

}