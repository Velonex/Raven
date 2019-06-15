#pragma once

namespace nfe {
	class OpenGLRenderer {
	public:
		static void setClearColorRGBA(float r, float g, float b, float a);
		static void clear();
	};
}