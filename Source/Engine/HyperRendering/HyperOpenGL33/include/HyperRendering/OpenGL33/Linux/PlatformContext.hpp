/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <HyperPlatform/Linux/Window.hpp>
#include <HyperRendering/OpenGL33/IPlatformContext.hpp>
#include <GL/glx.h>

namespace HyperRendering::OpenGL33::Linux
{
	class CPlatformContext final : public IPlatformContext
	{
	public:
		virtual bool initialize(HyperPlatform::CWindow& window) override;
		virtual void shutdown() override;

		virtual void swap_buffers() const override;

	private:
		HyperPlatform::Linux::CWindow* m_window{ nullptr };

		GLXContext m_graphics_context{ nullptr };
		XVisualInfo* m_visual_info{ nullptr };
	};
} // namespace HyperRendering::OpenGL33::Linux
