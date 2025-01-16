#pragma once

#include "RendererAPI.h"

namespace Bedrock
{
	class RenderCommand
	{
	public:
		inline static void SetClearColor(const glm::vec4& color) 
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void Draw(const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_RendererAPI->Draw(vertexArray);
		}

	private:
		static RendererAPI* s_RendererAPI;
	};
}