#pragma once
#include <NightFall/application/Window.h>
#include <NightFall/application/Input.h>
#include <GLFW/glfw3.h>

namespace nfe {

	class WindowsInput : public Input
	{
	public:
		WindowsInput();
		~WindowsInput();
	protected:
		virtual bool _isKeyPressed(int keyCode) override;
		virtual bool _isMousePressed(int mouseCode) override;
		virtual float _getMouseX() override;
		virtual float _getMouseY() override;
		virtual std::pair<float, float> _getMousePos() override;
	private:
		GLFWwindow* _window;
	private:
		static WindowsInput* _instance;
	};

}