#ifndef IMGUILAYER_H_
#define IMGUILAYER_H_

#include <NightFall/layers/Layer.h>
#include <NightFall/application/Window.h>

struct NightFallApplication;

namespace nfe {

	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();
		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onImGuiRender() override;

		void beginFrame();
		void endFrame();
	private:
		float _time;
		Window* _window;
	};

}

#endif