#pragma once

#include <Raven/rendering/GraphicsContext.h>

struct GLFWwindow;
namespace rvn {
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