#pragma once

#include "Core/Events/Event.h"
#include "Core/Time.h"

namespace Bedrock
{
	class Layer
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void OnUpdate(Time deltaTime) {}
		virtual void OnEvent(Event& e) {}
	};
}