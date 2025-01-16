#pragma once

#include "Layer.h"

namespace Bedrock
{
	class RenderLayer : public Layer
	{
	public:
		RenderLayer();
		~RenderLayer();

		void OnUpdate() override;

	private:

	};
}