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
		const std::string& getName() const { return _name; }
	private:
		const std::string& _name;
	};
}