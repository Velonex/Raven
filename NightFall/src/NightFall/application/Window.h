#ifndef WINDOW_H_
#define WINDOW_H_
#include <string>
#include <NightFall/event/EventHandler.h>

namespace nfe {
	struct WindowProps {
		typedef unsigned int uint;
		uint width, height;
		std::string title;
		WindowProps(uint width = 1280, uint height = 720, std::string title = "My Window") : width(width), height(height), title(title) { }
	};
	class Window {
		typedef unsigned int uint;
	public:
		static Window* createWindow(const WindowProps& props);

		virtual void onUpdate() = 0;

		virtual ~Window() {}

		virtual uint getWidth() const = 0;
		virtual uint getHeight() const = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool getVSync() const = 0;
#undef WaitCommEvent
		inline virtual void* getNativeWindow() const = 0;
	};
}

#endif