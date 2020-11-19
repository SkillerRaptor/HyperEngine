#pragma once

#include <string>

#include "HyperMath/Matrix.hpp"
#include "HyperMath/Vector.hpp"

namespace Hyperion
{
	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent& tagComponent) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}
	};

	struct TransformComponent
	{
		Vec3 Position;
		Vec3 Rotation;
		Vec3 Scale;

		TransformComponent() = default;
		TransformComponent(const TransformComponent& transformComponent) = default;
		TransformComponent(const Vec3& position, const Vec3& rotation, const Vec3& scale)
			: Position(position), Rotation(rotation), Scale(scale) {}
	};

	struct SpriteRendererComponent
	{
		Vec4 Color;

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent& spriteRendererComponent) = default;
		SpriteRendererComponent(const Vec4& color)
			: Color(color) {}
	};

	struct CameraComponent
	{
		uint32_t Width;
		uint32_t Height;

		float Zoom;
		float NearPlane;
		float FarPlane;

		Mat4 ProjectionMatrix = Mat4(1.0f);
		Mat4 TransformationMatrix = Mat4(1.0f);

		bool Primary;
		enum class CameraTypeInfo
		{
			ORTHOGRAPHIC,
			PROJECTION
		} CameraType;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
		CameraComponent(uint32_t width, uint32_t height, float zoom, float nearPlane, float farPlane, bool primary, CameraTypeInfo cameraType)
			: Width(width), Height(height), Zoom(zoom), NearPlane(nearPlane), FarPlane(farPlane), Primary(primary), CameraType(cameraType) {}
	};

	struct CameraControllerComponent
	{
		float MoveSpeed;
		float ZoomSpeed;

		CameraControllerComponent() = default;
		CameraControllerComponent(const CameraControllerComponent&) = default;
		CameraControllerComponent(float moveSpeed, float zoomSpeed)
			: MoveSpeed(moveSpeed), ZoomSpeed(zoomSpeed)  {}
	};

	struct CharacterControllerComponent 
	{
		float Speed;

		CharacterControllerComponent() = default;
		CharacterControllerComponent(const CharacterControllerComponent& characterControllerComponent) = default;
		CharacterControllerComponent(float speed)
			: Speed(speed) {}
	};
}
