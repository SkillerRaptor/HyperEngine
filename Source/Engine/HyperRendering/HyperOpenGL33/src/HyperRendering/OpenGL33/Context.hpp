/*
 * Copyright (c) 2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <HyperRendering/IContext.hpp>

namespace HyperRendering::OpenGL33
{
	class IPlatformContext;
	
	class CContext final : public IContext
	{
	public:
		CContext() = default;
		virtual ~CContext() override = default;
		
		virtual bool initialize(HyperPlatform::IWindow* window) override;
		virtual void shutdown() override;
		
		virtual void update() override;
	
	private:
		IPlatformContext* m_platform_context{ nullptr };
	};
}