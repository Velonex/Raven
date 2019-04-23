#include "LayerStack.h"
namespace nfe {

	LayerStack::LayerStack()
	{
	}
	LayerStack::~LayerStack()
	{
		for (Layer* l : _layers)
			_layers.pop_back();
		//for (Layer* l : _layers)
		//	delete l;
	}
	void LayerStack::pushLayer(Layer* layer)
	{
		_layers.emplace(_layers.begin() + _layerInsertIndex, layer);
		_layerInsertIndex++;
		layer->onAttach();
	}
	void LayerStack::pushOverlay(Layer* overlay)
	{
		_layers.emplace_back(overlay);
		overlay->onAttach();
	}
	void LayerStack::popLayer(Layer* layer)
	{
		layer->onDetach();
		auto it = std::find(_layers.begin(), _layers.end(), layer);
		if (it != _layers.end()) {
			_layers.erase(it);
			_layerInsertIndex--;
		}
	}
	void LayerStack::popOverlay(Layer* overlay)
	{
		overlay->onDetach();
		auto it = std::find(_layers.begin(), _layers.end(), overlay);
		if (it != _layers.end())
			_layers.erase(it);
	}
}