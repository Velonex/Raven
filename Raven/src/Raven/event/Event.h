#pragma once
#include <Raven/event/EventType.h>

namespace rvn {
	class Event {
	public:
		Event(EventType type, char* name) {
			this->_name = name;
			this->_type = type;
		}
		char* getName() { return _name; }
		EventType getType() { return _type; }
		bool handled = false;
	private:
		char* _name;
		EventType _type;
	};
}