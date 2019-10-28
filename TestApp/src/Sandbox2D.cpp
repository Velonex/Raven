#include "Sandbox2D.h"
#include <imgui.h>
#include <gtc/matrix_transform.hpp>
#include <Raven/core/Core.h>
#include <stb_image.h>
#include <gtc/type_ptr.hpp>

void Sandbox2D::onAttach() {
	_cameraController = rvn::createRef<rvn::OrthographicCameraController>(1280.0f / 720.0f, true);
}

void Sandbox2D::onUpdate(rvn::Timestep ts) {
	_cameraController->onUpdate(ts);
	rvn::Renderer2D::beginScene(_cameraController->getCamera());
	rvn::Renderer2D::drawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, _squareColor);
	rvn::Renderer2D::endScene();
}

void Sandbox2D::onImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square color", glm::value_ptr(_squareColor));
	ImGui::End();
}
