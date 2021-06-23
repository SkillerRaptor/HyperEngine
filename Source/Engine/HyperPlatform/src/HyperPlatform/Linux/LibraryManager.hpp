/*
 * Copyright (c) 2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <HyperPlatform/PlatformDetection.hpp>

#if HYPERENGINE_PLATFORM_LINUX
#	include <HyperCore/Memory/SparsePoolAllocator.hpp>
#	include <HyperPlatform/ILibraryManager.hpp>

namespace HyperPlatform::Linux
{
	class CLibraryManager final : public ILibraryManager
	{
	private:
		struct SLibraryData
		{
			uint32_t magic_number;

			std::string path;
			void* library;
		};

	public:
		CLibraryManager() = default;
		virtual ~CLibraryManager() override;

		virtual CLibraryHandle load(const std::string& path) override;
		virtual void unload(CLibraryHandle library_handle) override;

		virtual void* get_function_address(
			CLibraryHandle library_handle,
			const std::string& function) override;

	private:
		static void internal_unload(SLibraryData& data);

	private:
		HyperCore::CSparsePoolAllocator<SLibraryData> m_storage{ 256 };
		uint32_t m_version{ 1 };
	};
} // namespace HyperPlatform::Linux
#endif
