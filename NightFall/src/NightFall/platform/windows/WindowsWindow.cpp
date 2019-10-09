#include "WindowsWindow.h"
#include <NightFall/utils/Assert.h>
#include <NightFall/application/NightFallApplication.h>
#include <NightFall/event/events/WindowEvents.h>
#include <NightFall/event/events/KeyboardEvents.h>
#include <NightFall/event/events/MouseEvents.h>

namespace nfe {
	static bool glfwInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		LOG_ENGINE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	void WindowsWindow::onUpdate()
	{
		glfwPollEvents();
		_context->swapBuffers();
	}

	void WindowsWindow::_init(const WindowProps& props)
	{
		_windowData.height = props.height;
		_windowData.width = props.width;
		_windowData.title = props.title;
		_windowData.handler = NightFallApplication::getInstance()->getEventHandler();
		
		LOG_ENGINE_INFO("Creating Window: \"{0}\" ({1}, {2})", props.title, props.width, props.height);

		if (!glfwInitialized) {
			int success = glfwInit();
			ASSERT(success, "Couldn't initialize GLFW!")
			glfwSetErrorCallback(GLFWErrorCallback);
			glfwInitialized = true;
		}
		_window = glfwCreateWindow(props.width, props.height, props.title.c_str(), nullptr, nullptr);
		_context.reset(GraphicsContext::createGraphicsContext(_window));
		_context->init();
		glfwSetWindowUserPointer(_window, &_windowData);
		setVSync(true);

		glfwSetWindowCloseCallback(_window, [](GLFWwindow* window){
			_WindowData& data = *(_WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent* event = new WindowCloseEvent();
			data.handler->dispatchEvent(event);
		});
		glfwSetWindowSizeCallback(_window, [](GLFWwindow* window, int width, int height) {
			_WindowData& data = *(_WindowData*)glfwGetWindowUserPointer(window);
			data.width = width;
			data.height = height;
			WindowResizeEvent* event = new WindowResizeEvent(width, height);
			data.handler->dispatchEvent(event);
		});
		glfwSetCharCallback(_window, [](GLFWwindow* window, unsigned int keycode) {
			_WindowData& data = *(_WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent* event = new KeyTypedEvent(keycode);
			data.handler->dispatchEvent(event);
		});
		glfwSetKeyCallback(_window, [](GLFWwindow* window, int keycode, int scancode, int action, int mods) {
			_WindowData& data = *(_WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {
			case GLFW_PRESS: {
				KeyPressedEvent* ev = new KeyPressedEvent(keycode, 0);
				data.handler->dispatchEvent(ev);
				break;
			}
			case GLFW_REPEAT: {
				KeyPressedEvent* ev = new KeyPressedEvent(keycode, 1);
				data.handler->dispatchEvent(ev);
				break;
			}
			case GLFW_RELEASE: {
				KeyReleasedEvent* ev = new KeyReleasedEvent(keycode);
				data.handler->dispatchEvent(ev);
				break;
			}
			}
		});
		glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, int button, int action, int mods) {
			_WindowData& data = *(_WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {
			case GLFW_PRESS: {
				MouseButtonPressedEvent* event = new MouseButtonPressedEvent(button);
				data.handler->dispatchEvent(event);
				break;
			}
			case GLFW_RELEASE: {
				MouseButtonReleasedEvent* event = new MouseButtonReleasedEvent(button);
				data.handler->dispatchEvent(event);
				break;
			}
			}
		});
		glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double x, double y) {
			_WindowData& data = *(_WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent* event = new MouseMovedEvent((float)x, (float)y);
			data.handler->dispatchEvent(event);
		});
		glfwSetScrollCallback(_window, [](GLFWwindow* window, double xOff, double yOff) {
			_WindowData& data = *(_WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent* event = new MouseScrolledEvent((float)xOff, (float)yOff);
			data.handler->dispatchEvent(event);
		});
	}

	void WindowsWindow::_shutdown()
	{
		glfwDestroyWindow(_window);
	}

	unsigned int WindowsWindow::getWidth() const
	{
		return _windowData.width;
	}

	unsigned int WindowsWindow::getHeight() const
	{
		return _windowData.height;
	}

	void WindowsWindow::setVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		_windowData.vsync = enabled;
	}

	bool WindowsWindow::getVSync() const
	{
		return _windowData.vsync;
	}

	void * WindowsWindow::getNativeWindow() const
	{
		return _window;
	}

	GraphicsContext* WindowsWindow::getGraphicsContext() const
	{
		return _context.get();
	}

	Window* Window::createWindow(const WindowProps& props) {
		return new WindowsWindow(props);
	}
	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		_init(props);
	}
	WindowsWindow::~WindowsWindow()
	{
		_shutdown();
	}
}