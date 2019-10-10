#pragma once
#include <Raven/event/EventListener.h>
#include <Raven/event/EventType.h>
#include <Raven/event/Event.h>
#include <vector>
#include <Raven/logger/Logger.h>

namespace rvn {
	class EventHandler {
	public:
		void subscribe(EventListener* clazz, EventType type) {
			if (std::find(_subs.begin(), _subs.end(), _Subscriber(clazz, type)) != _subs.end()) {
				LOG_ENGINE_WARN("Instance with type {} has subscribed multiple times", type);
				return;
			}
			_subs.push_back({ clazz, type });
		}
		void dispatchEvent(Event* e) {
			// LOG_ENGINE_TRACE("Dispatched Event with type {}.", e->getName());
			for (int i = 0; i < _subs.size(); i++) {
				if ((e->getType() == _subs[i].type || _subs[i].type == rvn::EventType::ALL) && e->getType() != rvn::EventType::UNINITIALIZED) {
					_subs[i].clazz->onEvent(e);
				}
			}
			delete e;
		}
		void unsubscribe(EventListener* clazz, EventType type) {
			if (!(std::find(_subs.begin(), _subs.end(), _Subscriber(clazz, type)) != _subs.end())) {
				LOG_ENGINE_WARN("Instance that hasn't subscribed tried to unsubscribe");
				return;
			}
			_subs.erase(std::find(_subs.begin(), _subs.end(), _Subscriber(clazz, type)));
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
		std::vector<_Subscriber> _subs;
	};
}