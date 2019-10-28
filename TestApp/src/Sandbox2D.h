#pragma once
#include <Raven.h>

class Sandbox2D : public rvn::Layer {
public:
	Sandbox2D() {

	}
	virtual void onAttach() override;
	virtual void onEvent(rvn::Event* e) override {
		_cameraController->onEvent(e);
	}
	virtual void onUpdate(rvn::Timestep ts) override;
private:
	// Rendering Square
	ref<rvn::VertexArray> _vertexArraysq;
	glm::vec3 _squarePos;

	rvn::ShaderLibrary _shaderLib;
	ref<rvn::OrthographicCameraController> _cameraController;
};