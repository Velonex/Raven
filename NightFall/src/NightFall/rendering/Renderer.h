#pragma once

namespace nfe {

	enum class RendererAPI {
		None,
		OpenGL
	};

	class Renderer {
	public:
		inline static RendererAPI getAPI() { return s_rendererAPI; }
	private:
		static RendererAPI s_rendererAPI;
	};
}