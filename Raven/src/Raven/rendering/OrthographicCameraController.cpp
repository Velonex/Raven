#include "OrthographicCameraController.h"

#include <Raven/application/Input.h>
#include <Raven/application/KeyCodes.h>

namespace rvn {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: _aspectRatio(aspectRatio), _camera(-_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel), _rotation(rotation)
	{
	}

	void OrthographicCameraController::onUpdate(Timestep ts)
	{
		if (Input::isKeyPressed(KEY_A))
		{
			_cameraPosition.x -= cos(glm::radians(_rotation)) * _translationSpeed * ts;
			_cameraPosition.y -= sin(glm::radians(_rotation)) * _translationSpeed * ts;
		}
		else if (Input::isKeyPressed(KEY_D))
		{
			_cameraPosition.x += cos(glm::radians(_rotation)) * _translationSpeed * ts;
			_cameraPosition.y += sin(glm::radians(_rotation)) * _translationSpeed * ts;
		}

		if (Input::isKeyPressed(KEY_W))
		{
			_cameraPosition.x += -sin(glm::radians(_rotation)) * _translationSpeed * ts;
			_cameraPosition.y += cos(glm::radians(_rotation)) * _translationSpeed * ts;
		}
		else if (Input::isKeyPressed(KEY_S))
		{
			_cameraPosition.x -= -sin(glm::radians(_rotation)) * _translationSpeed * ts;
			_cameraPosition.y -= cos(glm::radians(_rotation)) * _translationSpeed * ts;
		}

		if (_doRotation)
		{
			if (Input::isKeyPressed(KEY_Q))
				_rotation += _rotationSpeed * ts;
			if (Input::isKeyPressed(KEY_E))
				_rotation -= _rotationSpeed * ts;

			if (_rotation > 180.0f)
				_rotation -= 360.0f;
			else if (_rotation <= -180.0f)
				_rotation += 360.0f;

			_camera.setRotation(_rotation);
		}

		_camera.setPosition(_cameraPosition);

		_translationSpeed = _zoomLevel;
	}

	void OrthographicCameraController::onEvent(Event* e)
	{
		switch (e->getType()) {
		case EVENT_WINDOW_RESIZE: 
			onWindowResized((WindowResizeEvent*)e);
			break;
		case EVENT_MOUSE_SCROLLED:
			onMouseScrolled((MouseScrolledEvent*)e);
			break;
		}
	}

	void OrthographicCameraController::onMouseScrolled(MouseScrolledEvent* e)
	{
		_zoomLevel -= e->getYOffset() * 0.25f;
		_zoomLevel = glm::max(_zoomLevel, 0.25f);
		_camera.setProjection(-_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel);
	}

	void OrthographicCameraController::onWindowResized(WindowResizeEvent* e)
	{
		_aspectRatio = (float)e->getWidth() / (float)e->getHeight();
		_camera.setProjection(-_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel);
	}

}