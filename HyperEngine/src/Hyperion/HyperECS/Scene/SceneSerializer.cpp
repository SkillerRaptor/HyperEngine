#include "SceneSerializer.hpp"

#include "HyperECS/Components.hpp"
#include "HyperECS/HyperEntity.hpp"
#include "HyperUtilities/HyperConfiguration/YAML/Configuration.hpp"
#include "HyperUtilities/HyperConfiguration/YAML/Node.hpp"

namespace Hyperion
{
	SceneSerializer::SceneSerializer(const Ref<Scene>& scene)
		: m_Scene(scene)
	{
	}

	bool SceneSerializer::Serialize(const std::string& filePath)
	{
		YAML::Configuration configuration(filePath);
		std::vector<YAML::Node> entities;

		m_Scene->Each([&](HyperEntity entity)
			{
				if (!entity)
					return;

				YAML::Node entityNode;

				entityNode["Entity"] = entity.GetComponent<TagComponent>().Tag;

				if (entity.HasComponent<TransformComponent>())
				{
					YAML::Node* componentNode = new YAML::Node();
					auto& component = entity.GetComponent<TransformComponent>();

					(*componentNode)["Position"] = component.Position;
					(*componentNode)["Rotation"] = component.Rotation;
					(*componentNode)["Scale"] = component.Scale;

					entityNode["TransformComponent"] = componentNode;
				}

				if (entity.HasComponent<SpriteRendererComponent>())
				{
					YAML::Node* componentNode = new YAML::Node();
					auto& component = entity.GetComponent<SpriteRendererComponent>();

					(*componentNode)["Color"] = component.Color;

					entityNode["SpriteRendererComponent"] = componentNode;
				}

				if (entity.HasComponent<CameraComponent>())
				{
					YAML::Node* componentNode = new YAML::Node();
					auto& component = entity.GetComponent<CameraComponent>();

					(*componentNode)["Zoom"] = component.Zoom;
					(*componentNode)["NearPlane"] = component.NearPlane;
					(*componentNode)["FarPlane"] = component.FarPlane;
					(*componentNode)["Primary"] = component.Primary;

					entityNode["CameraComponent"] = componentNode;
				}

				if (entity.HasComponent<CameraControllerComponent>())
				{
					YAML::Node* componentNode = new YAML::Node();
					auto& component = entity.GetComponent<CameraControllerComponent>();

					(*componentNode)["MoveSpeed"] = component.MoveSpeed;
					(*componentNode)["ZoomSpeed"] = component.ZoomSpeed;

					entityNode["CameraControllerComponent"] = componentNode;
				}

				if (entity.HasComponent<CharacterControllerComponent>())
				{
					YAML::Node* componentNode = new YAML::Node();
					auto& component = entity.GetComponent<CharacterControllerComponent>();

					(*componentNode)["Speed"] = component.Speed;

					entityNode["CharacterControllerComponent"] = componentNode;
				}

				entities.push_back(entityNode);
			});

		configuration["Scene"] = "Untitled";
		configuration["Entities"] = entities;

		configuration.Write();
		return false;
	}

	bool SceneSerializer::Deserialize(const std::string& filePath)
	{
		return false;
	}
}
