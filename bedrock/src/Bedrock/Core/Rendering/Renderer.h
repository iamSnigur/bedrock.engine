#pragma once

#include "RenderCommand.h"
#include "Camera.h"
#include "Shader.h"

namespace Bedrock 
{
	class Renderer
	{
	public:
		static void BeginScene(Camera& camera);
		static void EndScene();

		static void Submit(
			const std::shared_ptr<VertexArray>& vertexArray, 
			const std::shared_ptr<Shader>& shader,
			const Transform& modelTransform);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}