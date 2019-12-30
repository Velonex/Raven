#include <pch.h>
#include "WindowsInput.h"

namespace rvn {

	scope<Input> Input::_instance;
	WindowsInput::WindowsInput()
	{
		_window = (GLFWwindow*)Application::getInstance()->getWindow()->getNativeWindow();
	}

	WindowsInput::~WindowsInput()
	{
	}

	bool WindowsInput::_isKeyPressed(KeyCode keyCode)
	{
		return glfwGetKey(_window, (int)keyCode) == GLFW_PRESS;
	}

	bool WindowsInput::_isMousePressed(MouseCode mouseCode)
	{
		return glfwGetMouseButton(_window, (int)mouseCode) == GLFW_PRESS;
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