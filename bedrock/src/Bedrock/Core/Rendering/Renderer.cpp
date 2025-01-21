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

	void Renderer::Submit(
		const std::shared_ptr<VertexArray>& vertexArray, 
		const std::shared_ptr<Shader>& shader,
		const Transform& modelTransform)
	{
		vertexArray->Bind();
		shader->Bind();
		shader->SetUniformMat4f("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		shader->SetUniformMat4f("u_Model", modelTransform.GetModelMatrix());

		RenderCommand::Draw(vertexArray);
	}
}