#ifndef EVENTLISTENER_H_
#define EVENTLISTENER_H_
#include <NightFall/event/Event.h>

namespace nfe {
	struct EventListener {
		virtual void onEvent(Event* e) = 0;
	};
}
#endif