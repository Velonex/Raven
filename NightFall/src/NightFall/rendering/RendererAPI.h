#pragma once

#include <glm.hpp>
#include <NightFall/core/Core.h>
#include "VertexArray.h"

namespace nfe {

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
 	private:
		static API s_rendererAPI;
	};

}