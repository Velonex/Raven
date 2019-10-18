#pragma once

#include <Raven/event/Event.h>
#include <Raven/core/Timestep.h>
#include <Raven/rendering/OrthographicCamera.h>
#include <glm.hpp>
#include <Raven/event/events/MouseEvents.h>
#include <Raven/event/events/WindowEvents.h>

namespace rvn {

	class OrthographicCameraController {
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void onEvent(Event* e);
		void onUpdate(Timestep ts);

		OrthographicCamera& getCamera() { return _camera; }
		const OrthographicCamera& getCamera() const { return _camera; }

		float getZoomLevel() const { return _zoomLevel; }
		void setZoomLevel(float zoomLevel) { _zoomLevel = zoomLevel; }
	private:
		void onWindowResized(WindowResizeEvent* e);
		void onMouseScrolled(MouseScrolledEvent* e);
	private:
		float _aspectRatio;
		float _zoomLevel = 1.0f;
		OrthographicCamera _camera;

		bool _doRotation;
		
		glm::vec3 _cameraPosition = { 0.0f, 0.0f, 0.0f };
		float _rotation = 0.0f;
		float _translationSpeed = 5.0f, _rotationSpeed = 180.0f;
	};

}