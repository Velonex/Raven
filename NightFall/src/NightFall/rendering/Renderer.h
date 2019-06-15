#pragma once

namespace nfe {

	enum class RendererAPI {
		None,
		OpenGL
	};

	class Renderer {
	public:
		inline static RendererAPI getAPI() { return s_rendererAPI; }
		static void setClearColorRGBA(float r, float g, float b, float a);
	private:
		static RendererAPI s_rendererAPI;
	};
}