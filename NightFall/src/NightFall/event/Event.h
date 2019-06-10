#pragma once
#include <NightFall/event/EventType.h>

namespace nfe {
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