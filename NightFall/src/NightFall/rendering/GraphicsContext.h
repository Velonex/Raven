#ifndef GRAPHICS_CONTEXT_H_
#define GRAPHICS_CONTEXT_H_

namespace nfe {
	class Window;
	class GraphicsContext {
	public:
		virtual void init() = 0;
		virtual void swapBuffers() = 0;
		static GraphicsContext* createGraphicsContext(void* window);
	};
}
#endif