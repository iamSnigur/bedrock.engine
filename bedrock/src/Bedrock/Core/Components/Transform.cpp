#include "Transform.h"

namespace Bedrock
{
	Transform::Transform()
		: m_Position{ glm::vec3{1.0} },
		  m_Rotation{ glm::toQuat(glm::mat4(1.0)) },
		  m_Scale{ glm::vec3{1.0} }
	{
		UpdateModelMatrix();
	}

	Transform::Transform(glm::vec3& position, glm::quat& rotation, glm::vec3& scale)
		: m_Position{ position },
		  m_Rotation{ rotation },
		  m_Scale{ scale }
	{
		UpdateModelMatrix();
	}

	void Transform::UpdateModelMatrix()
	{
		m_ModelMatrix =
			  glm::translate(glm::mat4(1.0), m_Position)
			* glm::toMat4(m_Rotation)
			* glm::scale(glm::mat4(1.0), m_Scale);
	}
}