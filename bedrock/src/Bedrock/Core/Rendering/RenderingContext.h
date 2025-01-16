#pragma once

namespace Bedrock
{
	class RenderingContext
	{
	public:
		virtual void Boot() = 0;
		//virtual void Shutdown() = 0;
		virtual void SwapBuffers() = 0;
	};
}