#pragma once
#include <Raven/application/Application.h>
#include <utility>

namespace rvn {
	class Input {
		friend class Application;
	public:
		static bool isKeyPressed(int keyCode) { return _instance->_isKeyPressed(keyCode); }
		static bool isMousePressed(int mouseCode) { return _instance->_isMousePressed(mouseCode); }
		static float getMouseX() { return _instance->_getMouseX(); }
		static float getMouseY() { return _instance->_getMouseY(); }
		static std::pair<float, float> getMousePos() { return _instance->_getMousePos(); }
	protected:
		virtual bool _isKeyPressed(int keyCode) = 0;
		virtual bool _isMousePressed(int mouseCode) = 0;
		virtual float _getMouseX() = 0;
		virtual float _getMouseY() = 0;
		virtual std::pair<float, float> _getMousePos() = 0;
	private:
		static void setInstance(Input* instance) { _instance.reset(instance); }
		static Input* createInput();
		static scope<Input> _instance;
	};
}