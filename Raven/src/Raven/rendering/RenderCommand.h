#pragma once

#include "RendererAPI.h"

namespace rvn {

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
		inline static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
			s_api->setViewport(x, y, width, height);
		}
	private:
		static scope<RendererAPI> s_api;
	};

}