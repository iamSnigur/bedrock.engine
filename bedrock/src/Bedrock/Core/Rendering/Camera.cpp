#include "Camera.h"

namespace Bedrock
{
	Camera::Camera(float fieldOfView, float width, float height)
		: m_ProjectionMatrix{ glm::perspectiveFov(glm::radians(fieldOfView), width, height, 0.1f, 100.0f) },
		  m_ViewMatrix{ glm::mat4(1.0f) }
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera::UpdateViewMatrix()
	{
		m_ViewMatrix = glm::inverse(m_Transform.GetModelMatrix());
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}