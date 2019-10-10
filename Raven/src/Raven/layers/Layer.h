#pragma once
#include <string>
#include <Raven/event/Event.h>
#include <Raven/core/Timestep.h>
namespace rvn {
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