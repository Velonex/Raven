#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_
#include <NightFall/event/EventListener.h>
#include <NightFall/event/EventType.h>
#include <NightFall/event/Event.h>
#include <NightFall/logger/Logger.h>
#include <NightFall/datatypes/ArrayList.h>

namespace nfe {
	class EventHandler {
	public:
		void subscribe(EventListener* clazz, EventType type) {
			if (_subs.contains(_Subscriber(clazz, type))) {
				LOG_ENGINE_WARN("Instance with type {} has subscribed multiple times", type);
				return;
			}
			_subs.add({ clazz, type });
		}
		void dispatchEvent(Event* e) {
			// LOG_ENGINE_TRACE("Dispatched Event with type {}.", e->getName());
			for (int i = 0; i < _subs.size(); i++) {
				if ((e->getType() == _subs[i].type || _subs[i].type == nfe::EventType::ALL) && e->getType() != nfe::EventType::UNINITIALIZED) {
					_subs[i].clazz->onEvent(e);
				}
			}
			delete e;
		}
		void unsubscribe(EventListener* clazz, EventType type) {
			if (!_subs.contains(_Subscriber(clazz, type))) {
				LOG_ENGINE_WARN("Instance that hasn't subscribed tried to unsubscribe");
				return;
			}
			_subs.remove(_subs.indexOf(_Subscriber(clazz, type)));
		}
	private:
		struct _Subscriber {
			EventListener* clazz;
			EventType type;
			bool operator==(_Subscriber rhs) {
				return rhs.clazz == clazz && rhs.type == type;
			}
			_Subscriber(EventListener* clazz, EventType type) : clazz(clazz), type(type) {

			}
			_Subscriber() : clazz(nullptr), type(EventType::UNINITIALIZED) {

			}
		};
		nfe::ArrayList<_Subscriber> _subs;
	};
}
#endif