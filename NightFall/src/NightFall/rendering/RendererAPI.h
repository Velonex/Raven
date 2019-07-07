#pragma once

#include <glm.hpp>
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

		virtual void drawIndexed(const VertexArray* vertexArray) = 0;

		inline static API getAPI() { return s_rendererAPI; }
	private:
		static API s_rendererAPI;
	};

}