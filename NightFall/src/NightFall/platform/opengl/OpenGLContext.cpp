#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/GL.h>
#include <NightFall/application/NightFallApplication.h>
#include <NightFall/logger/Logger.h>

namespace nfe {
	OpenGLContext::OpenGLContext(GLFWwindow* window)
	{
		_window = window;
	}
	void OpenGLContext::init()
	{
		glfwMakeContextCurrent(_window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ASSERT(status, "Couldn't initialize Glad!");
		
		LOG_ENGINE_TRACE("Renderer: OpenGL {0}", glGetString(GL_VERSION));
		LOG_ENGINE_TRACE("GPU: {0}, {1}", glGetString(GL_VENDOR), glGetString(GL_RENDERER));
	}
	void OpenGLContext::swapBuffers()
	{
		glfwSwapBuffers(_window);
	}

	GraphicsContext* GraphicsContext::createGraphicsContext(void* window) {
		return new OpenGLContext((GLFWwindow*)window);
	}
}