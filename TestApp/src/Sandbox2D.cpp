#include "Sandbox2D.h"
#include <imgui.h>
#include <gtc/matrix_transform.hpp>
#include <Raven/core/Core.h>
#include <stb_image.h>
#include <gtc/type_ptr.hpp>
#include <Raven/utils/Instrumentor.h>

void Sandbox2D::onAttach() {
	_cameraController = rvn::createRef<rvn::OrthographicCameraController>(1280.0f / 720.0f, true);
	_chess = rvn::Texture2D::create("assets/textures/chess.png");
	_trans = rvn::Texture2D::create("assets/textures/blend.png");
}

void Sandbox2D::onUpdate(rvn::Timestep ts) {
	RVN_PROFILE_FUNCTION();
	{
		RVN_PROFILE_SCOPE("CameraController::onUpdate");
		_cameraController->onUpdate(ts);
	}
	{
		RVN_PROFILE_SCOPE("Renderer draw");
		rvn::Renderer2D::beginScene(_cameraController->getCamera());
		//rvn::Renderer2D::drawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, _squareColor);
		rvn::Renderer2D::drawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, _chess, _squareColor, _tilingFactor);
		rvn::Renderer2D::drawQuad({ 0.0f, 0.0f, 0.0f }, { 10.0f, 10.0f }, _trans);
		rvn::Renderer2D::endScene();
	}
}

void Sandbox2D::onImGuiRender()
{
	RVN_PROFILE_FUNCTION();
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square color", glm::value_ptr(_squareColor));
	ImGui::SliderFloat("Square tiling factor", &_tilingFactor, 0.f, 10.f, "%.3f");
	ImGui::End();
}
