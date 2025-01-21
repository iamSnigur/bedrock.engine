#pragma once

#include "glm/glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/quaternion.hpp"

namespace Bedrock
{
	class Transform
	{
	public:
		Transform(const glm::vec3& position = glm::vec3{ 0.0f },
			const glm::quat& rotation = glm::quat{},
			const glm::vec3& scale = glm::vec3{ 1.0f })
			: m_Position(position), m_Rotation(rotation), m_Scale(scale)
		{
			UpdateModelMatrix();
		}

		const glm::mat4& GetModelMatrix() const { return m_ModelMatrix; }
		const glm::vec3& GetPosition() const { return m_Position; }
		const glm::quat& GetRotation() const { return m_Rotation; }
		const glm::vec3& GetScale() const { return m_Scale; }

		void SetPosition(const glm::vec3& position) { m_Position = position; UpdateModelMatrix(); }
		void SetRotation(const glm::quat& rotation) { m_Rotation = rotation; UpdateModelMatrix(); }
		void SetScale(const glm::vec3& scale) { m_Scale = scale; UpdateModelMatrix(); }

	private:
		glm::vec3 m_Position;
		glm::quat m_Rotation;
		glm::vec3 m_Scale;

		glm::mat4 m_ModelMatrix;

		void UpdateModelMatrix()
		{
			m_ModelMatrix =
				  glm::translate(glm::mat4(1.0), m_Position)
				* glm::toMat4(m_Rotation)
				* glm::scale(glm::mat4(1.0), m_Scale);
		}
	};
}