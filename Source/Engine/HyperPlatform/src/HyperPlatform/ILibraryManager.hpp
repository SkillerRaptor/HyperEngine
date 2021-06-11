/*
 * Copyright (c) 2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <HyperCore/Utilities/Prerequisites.hpp>
#include <cstdint>
#include <string>

namespace HyperPlatform
{
	struct SLibraryHandle
	{
		static constexpr const uint32_t s_index_mask{ HyperCore::Mask32(16) };
		static constexpr const uint32_t s_version_mask{ ~HyperCore::Mask32(16) };
		
		uint32_t handle{ 0 };
		
		bool valid() const noexcept;
		
		uint16_t index() const noexcept;
		uint16_t version() const noexcept;
		
		bool operator==(const SLibraryHandle& library_handle) const noexcept;
		bool operator!=(const SLibraryHandle& library_handle) const noexcept;
	};
	
	class ILibraryManager
	{
	public:
		ILibraryManager() = default;
		virtual ~ILibraryManager() = default;
		
		virtual SLibraryHandle load(const std::string& path) = 0;
		virtual void unload(SLibraryHandle library_handle) = 0;
		
		virtual void* get_function_address(SLibraryHandle library_handle, const std::string& function) = 0;
	
		static ILibraryManager* construct();
	};
}