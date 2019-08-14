#pragma once
#include <string>
#include <NightFall/event/Event.h>
#include <NightFall/core/Timestep.h>
namespace nfe {
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		~Layer();
		virtual void onEvent(Event* e) {}
		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate(Timestep ts) {}
		virtual void onImGuiRender() {}
		std::string& getName() const { return _name; }
	private:
		std::string& _name;
	};
}