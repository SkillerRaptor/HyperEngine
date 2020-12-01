#pragma once

#include <queue>

#include "HyperUtilities/NonCopyable.hpp"
#include "HyperUtilities/NonMoveable.hpp"

namespace Hyperion
{
	enum class TextureType
	{
		DEFAULT,
		DIFFUSE,
		FRAMEBUFFER,
		HEIGHT,
		NORMAL,
		SPECULAR
	};

	struct TextureData
	{
		uint32_t Width = 0;
		uint32_t Height = 0;
		uint8_t Channels = 0;
		unsigned char* Data = nullptr;

		std::string Path = "";
		TextureType TextureType = TextureType::DEFAULT;
	};

	struct TextureHandle
	{
		uint32_t Handle;

		bool IsHandleValid() const { return Handle != 0; }
		bool operator==(const TextureHandle& textureHandle) const { return Handle == textureHandle.Handle; }
	};

	struct TextureHandleHasher
	{
		size_t operator()(const TextureHandle& textureHandle) const { return (std::hash<uint32_t>()(textureHandle.Handle)); }
	};

	class TextureManager : public NonCopyable, NonMoveable
	{
	protected:
		std::queue<TextureHandle> m_TextureIds;

	public:
		TextureManager() = default;
		virtual ~TextureManager() = default;

		virtual TextureHandle CreateTexture(const std::string& path, TextureType textureType = TextureType::DEFAULT) = 0;
		virtual TextureHandle CreateTexture(uint32_t width, uint32_t height, TextureType textureType = TextureType::DEFAULT) = 0;
		virtual void GenerateTexture(TextureData* textureData, bool alpha) = 0;
		virtual bool BindTexture(TextureHandle handle, uint32_t textureSlot) = 0;
		virtual bool DeleteTexture(TextureHandle handle) = 0;
		virtual bool DeleteTextureData(TextureHandle handle) = 0;

		virtual void SetWidth(TextureHandle handle, uint32_t width) = 0;
		virtual uint32_t GetWidth(TextureHandle handle) = 0;

		virtual void SetHeight(TextureHandle handle, uint32_t height) = 0;
		virtual uint32_t GetHeight(TextureHandle handle) = 0;

		virtual void SetTextureType(TextureHandle handle, TextureType textureType) = 0;
		virtual TextureType GetTextureType(TextureHandle handle) = 0;

		virtual uint8_t GetChannels(TextureHandle handle) = 0;
		virtual const unsigned char* GetData(TextureHandle handle) = 0;
		virtual const std::string& GetPath(TextureHandle handle) = 0;
		virtual TextureData* GetTextureData(TextureHandle handle) = 0;
	};
}
