#pragma once
#include <NightFall/logger/Logger.h>
#include <NightFall/application/Window.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace nfe {
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		~WindowsWindow();

		virtual void onUpdate() override;

		virtual unsigned int getWidth() const override;
		virtual unsigned int getHeight() const override;

		virtual void setVSync(bool enabled) override;
		virtual bool getVSync() const override;

		inline virtual void* getNativeWindow() const override;

		virtual GraphicsContext* getGraphicsContext() const override;
	private:
		virtual void _init(const WindowProps& props);
		virtual void _shutdown();
	private:
		GLFWwindow* _window;
		GraphicsContext* _context;
		struct _WindowData {
			unsigned int width, height;
			std::string title;
			bool vsync;
			nfe::EventHandler* handler;
		} _windowData;
	};
}