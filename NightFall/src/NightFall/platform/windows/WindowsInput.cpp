#include "WindowsInput.h"

namespace nfe {

	Input* Input::_instance = nullptr;
	WindowsInput::WindowsInput()
	{
		_window = (GLFWwindow*)NightFallApplication::getInstance()->getWindow()->getNativeWindow();
	}

	WindowsInput::~WindowsInput()
	{
	}

	bool WindowsInput::_isKeyPressed(int keyCode)
	{
		return glfwGetKey(_window, keyCode) == GLFW_PRESS;
	}

	bool WindowsInput::_isMousePressed(int mouseCode)
	{
		return glfwGetMouseButton(_window, mouseCode) == GLFW_PRESS;
	}

	float WindowsInput::_getMouseX()
	{
		double x, y;
		glfwGetCursorPos(_window, &x, &y);
		return (float)x;
	}

	float WindowsInput::_getMouseY()
	{
		double x, y;
		glfwGetCursorPos(_window, &x, &y);
		return (float)y;
	}

	std::pair<float, float> WindowsInput::_getMousePos()
	{
		double x, y;
		glfwGetCursorPos(_window, &x, &y);
		return {x, y};
	}

	Input* Input::createInput() {
		return new WindowsInput();
	}
}