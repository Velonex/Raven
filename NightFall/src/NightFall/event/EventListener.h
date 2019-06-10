#pragma once
#include <NightFall/event/Event.h>

namespace nfe {
	struct EventListener {
		virtual void onEvent(Event* e) = 0;
	};
}