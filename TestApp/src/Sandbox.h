#pragma once
#include <Raven.h>

class Sandbox : public rvn::Layer {
public:
	Sandbox() {

	}
	virtual void onAttach() override;
	virtual void onEvent(rvn::Event* e) override {
		_cameraController->onEvent(e);
	}
	virtual void onUpdate(rvn::Timestep ts) override;
private:
	// Rendering Square
	ref<rvn::VertexArray> _vertexArraysq;
	ref<rvn::Texture2D> _texsq;
	ref<rvn::Texture2D> _texsq2;
	glm::vec3 _squarePos;

	rvn::ShaderLibrary _shaderLib;
	ref<rvn::OrthographicCameraController> _cameraController;
};