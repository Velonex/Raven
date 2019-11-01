#pragma once
#include <Raven.h>
#include <Raven/rendering/Renderer2D.h>

class Sandbox2D : public rvn::Layer {
public:
	Sandbox2D() {

	}
	virtual void onAttach() override;
	virtual void onEvent(rvn::Event* e) override {
		_cameraController->onEvent(e);
	}
	virtual void onUpdate(rvn::Timestep ts) override;
	virtual void onImGuiRender() override;
private:
	ref<rvn::OrthographicCameraController> _cameraController;
	glm::vec4 _squareColor = { 0.9f, 0.2f, 0.7f, 1.0f };
	ref<rvn::Texture2D> _chess;
};