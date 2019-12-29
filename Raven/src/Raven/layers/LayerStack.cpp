#include <pch.h>
#include "LayerStack.h"
namespace rvn {

	LayerStack::LayerStack()
	{
	}
	LayerStack::~LayerStack()
	{
		for (Layer* l : _layers) {
			l->onDetach();
			_layers.pop_back();
		}
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