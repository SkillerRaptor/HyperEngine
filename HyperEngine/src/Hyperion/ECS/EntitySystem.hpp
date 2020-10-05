#pragma once

#include "Registry.hpp"
#include "Utilities/Timestep.hpp"

namespace Hyperion
{
	class EntitySystem
	{
	public:
		EntitySystem();
		~EntitySystem();

		virtual void Tick(Registry& registry, int currentTick) {};
		virtual void Update(Registry& registry, Timestep timeStep) {};
		virtual void Render(Registry& registry) {};
	};
}