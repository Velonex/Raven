#pragma once
#include <NightFall\event\Event.h>

namespace nfe {
	class KeyEvent : public Event {
	public:
		inline int getKeyCode() const { return _keycode; }
	protected:
		KeyEvent(int keycode, EventType type, char* name) : Event(type, name), _keycode(keycode) {}
		int _keycode;
	};
	class KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int keycode, int repeats) : KeyEvent(keycode, EventType::EVENT_KEY_PRESSED, "KeyPressedEvent"), _repeatCount(repeats) {}
	private:
		int _repeatCount;
	};
	class KeyTypedEvent : public KeyEvent {
	public:
		KeyTypedEvent(int keycode) : KeyEvent(keycode, EventType::EVENT_KEY_TYPED, "KeyTypedEvent") {}
	};
	class KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keycode) : KeyEvent(keycode, EventType::EVENT_KEY_RELEASED, "KeyReleasedEvent") {}
	};
};