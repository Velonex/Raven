#ifndef LAYERSTACK_H_
#define LAYERSTACK_H_
#include <NightFall/layers/Layer.h>
#include <vector>
namespace nfe {
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);
		void popLayer(Layer* layer);
		void popOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return _layers.begin(); }
		std::vector<Layer*>::iterator end() { return _layers.end(); }
	private:
		std::vector<Layer*> _layers;
		uint32_t _layerInsertIndex = 0;
	};
}
#endif