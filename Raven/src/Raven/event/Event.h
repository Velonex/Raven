#pragma once
#include <Raven/event/EventType.h>

namespace rvn {
	class Event {
	public:
		Event(EventType type, char* name) {
			this->name = name;
			this->type = type;
		}
		char* getName() { return name; }
		EventType getType() { return type; }
	private:
		char* name;
		EventType type;
	};
}