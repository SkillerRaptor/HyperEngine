#pragma once

#include "HyperECS/Components.hpp"
#include "HyperECS/HyperECS.hpp"
#include "HyperEvents/MouseEvents.hpp"
#include "HyperUtilities/Input.hpp"

namespace Hyperion
{
	class CameraControllerSystem : public System
	{
	public:
		CameraControllerSystem() {};
		virtual ~CameraControllerSystem() {};

		virtual void OnUpdate(Registry& registry, Timestep timeStep) override
		{
			registry.Each<CameraControllerComponent, CameraComponent, TransformComponent>([&](Entity entity, CameraControllerComponent& cameraController, CameraComponent& cameraComponent, TransformComponent& transform)
				{
					transform.Position.x -= (float)(cameraController.MoveSpeed * timeStep * Input::GetAxis(InputAxis::HORIZONTAL));
					transform.Position.y += (float)(cameraController.MoveSpeed * timeStep * Input::GetAxis(InputAxis::VERTICAL));
				});
		}

		virtual void OnEvent(Registry& registry, Event& event) override
		{
			EventDispatcher dispatcher(event);
			
			dispatcher.Dispatch<MouseScrolledEvent>([&](MouseScrolledEvent& e)
				{
					registry.Each<CameraControllerComponent, CameraComponent, TransformComponent>([&](Entity entity, CameraControllerComponent& cameraController, CameraComponent& cameraComponent, TransformComponent& transform)
						{
							float& zoom = cameraComponent.Zoom;
							zoom -= e.GetYOffset() * cameraController.ZoomSpeed;
							zoom = (zoom < cameraController.ZoomSpeed) ? cameraController.ZoomSpeed : zoom;
						});
					return false;
				});
		}
	};
}
