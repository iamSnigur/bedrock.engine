#pragma once

#include "glm/glm.hpp"
#include "Core/Components/Transform.h"

namespace Bedrock
{
	class Camera
	{
	public:
		Camera(float fieldOfView, float width, float height);

		void SetTransform(const Transform& transform) { m_Transform = transform;  UpdateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() { return m_ViewProjectionMatrix; }
		Transform& GetTransform() { return m_Transform; }

		void UpdateViewMatrix();

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		Transform m_Transform;		
	};
}
