#pragma once
#include <NightFall/application/NightFallApplication.h>
#include <utility>

namespace nfe {
	class Input {
		friend class NightFallApplication;
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
		static void setInstance(Input* instance) { _instance = instance; }
		static Input* createInput();
		static Input* _instance;
	};
}