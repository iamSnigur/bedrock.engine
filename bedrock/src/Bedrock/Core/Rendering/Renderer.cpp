#include "Renderer.h"

namespace Bedrock
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(Camera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader)
	{
		vertexArray->Bind();
		shader->Bind();
		shader->SetUniformMat4f("u_ViewProjection", m_SceneData->ViewProjectionMatrix);

		glm::mat4 modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(2.0f, 2.0f, 2.0f));
		modelMatrix = glm::rotate(modelMatrix, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		shader->SetUniformMat4f("u_Model", modelMatrix);

		RenderCommand::Draw(vertexArray);
	}
}