#ifndef MOUSEEVENTS_H_
#define MOUSEEVENTS_H_
#include <NightFall\event\Event.h>
namespace nfe {
	class MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float x, float y) : Event(EventType::EVENT_MOUSE_MOVED, "MouseMovedEvent"), _x(x), _y(y) { }
		inline float getX() const { return _x; }
		inline float getY() const { return _y; }
	private:
		float _x, _y;
	};
	class MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(float xOff, float yOff) : Event(EventType::EVENT_MOUSE_SCROLLED, "MouseScrolledEvent"), _xOffset(xOff), _yOffset(yOff) { }
		inline float getXOffset() const { return _xOffset; }
		inline float getYOffset() const { return _yOffset; }
	private:
		float _xOffset, _yOffset;
	};
	class MouseEvent : public Event {
	public:
		inline int getMouseButton() const { return _button; }
	protected:
		MouseEvent(int button, EventType type, char* name) : Event(type, name), _button(button) {}
		int _button;
	};
	class MouseButtonReleasedEvent : public MouseEvent {
	public:
		MouseButtonReleasedEvent(int button) : MouseEvent(button, EventType::EVENT_MOUSE_BUTTON_RELEASED, "MouseReleasedEvent") { }
	};
	class MouseButtonPressedEvent : public MouseEvent {
	public:
		MouseButtonPressedEvent(int button) : MouseEvent(button, EventType::EVENT_MOUSE_BUTTON_PRESSED, "MousePressedEvent") { }
	};
}
#endif