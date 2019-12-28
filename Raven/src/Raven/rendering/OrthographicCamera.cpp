#include "OrthographicCamera.h"

#include <gtc/matrix_transform.hpp>
#include <Raven/utils/Instrumentor.h>

namespace rvn {
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: _projectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), _viewMatrix(1.0f)
	{
		RVN_PROFILE_FUNCTION();
		_vpMatrix = _projectionMatrix * _viewMatrix;
	}
	void OrthographicCamera::setProjection(float left, float right, float bottom, float top)
	{
		RVN_PROFILE_FUNCTION();
		_projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		_vpMatrix = _projectionMatrix * _viewMatrix;
	}
	void OrthographicCamera::recalculateViewMatrix()
	{
		RVN_PROFILE_FUNCTION();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), _position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(_rotation), glm::vec3(0, 0, 1));

		_viewMatrix = glm::inverse(transform);
		_vpMatrix = _projectionMatrix * _viewMatrix;
	}
}