#pragma once
#include <Raven/event/Event.h>

namespace rvn {
	struct EventListener {
		virtual void onEvent(Event* e) = 0;
	};
}