/*
 * Copyright (c) 2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <HyperCore/Assertion.hpp>
#include <HyperPlatform/PlatformDetection.hpp>
#include <HyperRendering/OpenGL33/IPlatformContext.hpp>

#if HYPERENGINE_PLATFORM_WINDOWS
#include <HyperRendering/OpenGL33/Windows/PlatformContext.hpp>
#elif HYPERENGINE_PLATFORM_LINUX
#include <HyperRendering/OpenGL33/Linux/PlatformContext.hpp>
#endif

namespace HyperRendering::OpenGL33
{
	IPlatformContext* IPlatformContext::construct()
	{
#if HYPERENGINE_PLATFORM_WINDOWS
		return new Windows::CPlatformContext();
#elif HYPERENGINE_PLATFORM_LINUX
		return new Linux::CPlatformContext();
#else
		HYPERENGINE_ASSERT_NOT_REACHED();
#endif
	}
}
