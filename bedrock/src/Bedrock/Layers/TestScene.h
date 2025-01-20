#pragma once

#include <memory>

#include "Layers/Layer.h"
#include "Core/Rendering/Camera.h"
#include "Core/Rendering/Shader.h"
#include "Core/Rendering/Buffer.h"
#include "Core/Rendering/VertexArray.h"
#include "Core/Events/EventDispatcher.h"

namespace Bedrock
{
	class TestScene : public Layer
	{
	public:
		TestScene();
		~TestScene();

		virtual void OnUpdate(Time deltaTime) override;
		virtual void OnEvent(Event& e) override;

	private:
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;
		Camera m_Camera;
		EventDispatcher m_EventDispatcher;
		glm::vec2 m_PreviousMousePos;
		glm::vec3 m_CameraRotation;
		glm::vec3 m_CameraPosition;

		void OnKeyPress(KeyPressEvent& e);
	};
}