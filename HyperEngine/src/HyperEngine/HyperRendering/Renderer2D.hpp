#pragma once

#include <glm/glm.hpp>

#include "HyperECS/HyperComponents/Components.hpp"
#include "HyperRendering/Renderer.hpp"

namespace HyperRendering
{
	struct CameraInfo
	{
		glm::vec3 Position;

		size_t Width;
		size_t Height;

		float Zoom;
		float NearPlane;
		float FarPlane;
	};

	class Renderer2D : public Renderer
	{
	protected:
		const uint32_t MaxQuads = 2000;
		const uint32_t MaxVertices = MaxQuads * 4;
		const uint32_t MaxIndices = MaxQuads * 6;
		const uint32_t MaxTextureSlots = 32; // TODO: RenderCaps

		uint32_t m_QuadCount = 0;
		uint32_t m_QuadIndexCount = 0;
		uint32_t m_DrawCalls = 0;

		std::vector<TextureHandle> m_TextureSlots;
		uint32_t m_TextureSlotIndex = 1;

	public:
		Renderer2D() = default;
		virtual ~Renderer2D() = default;

		virtual void Setup() = 0;

		virtual void BeginScene() = 0;
		virtual void EndScene() = 0;

		virtual void Flush() = 0;

		virtual void DrawQuad(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale, const glm::vec4& color) = 0;
		virtual void DrawQuad(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale, TextureHandle texture) = 0;
		virtual void DrawQuad(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale, const glm::vec4& color, TextureHandle texture) = 0;

		virtual void SetCamera(const glm::vec3& position, const glm::vec3& rotation, float fov, const glm::vec2& clippingPlanes, const glm::vec2& viewportRect, HyperECS::CameraComponent::ProjectionType projectionType) = 0;
		virtual void SetCamera(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) = 0;

		inline void SetShaderManager(HyperCore::Ref<ShaderManager> shaderManager)
		{
			m_ShaderManager = shaderManager;
		}

		inline void SetTextureManager(HyperCore::Ref<TextureManager> textureManager)
		{
			m_TextureManager = textureManager;
		}

		inline void SetSceneRecorder(HyperCore::Ref<SceneRecorder> sceneRecorder)
		{
			m_SceneRecorder = sceneRecorder;
		}

	protected:
		virtual void StartBatch() = 0;
		virtual void NextBatch() = 0;
	};
}