#pragma once

#include <glm.hpp>
#include <Raven/core/Core.h>
#include "VertexArray.h"

namespace rvn {

	class RendererAPI {
	public:
		enum class API {
			None,
			OpenGL
		};
	public:
		virtual void setClearColorRGBA(const glm::vec4& color) = 0;
		virtual void clear() = 0;

		virtual void drawIndexed(const ref<VertexArray>& vertexArray) = 0;

		inline static API getAPI() { return s_rendererAPI; }

		virtual void init() = 0;

		virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
 	private:
		static API s_rendererAPI;
	};

}