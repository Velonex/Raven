#ifndef OPENGL_CONTEXT_H_
#define OPENGL_CONTEXT_H_

#include <NightFall/rendering/GraphicsContext.h>

struct GLFWwindow;
namespace nfe {
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* window);
		virtual void init() override;
		virtual void swapBuffers() override;
	private:
		GLFWwindow* _window = nullptr;
	};

}
#endif