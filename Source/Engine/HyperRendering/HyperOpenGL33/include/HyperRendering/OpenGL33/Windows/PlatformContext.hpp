/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <HyperPlatform/Window.hpp>
#include <HyperRendering/OpenGL33/IPlatformContext.hpp>
#include <GL/gl.h>

namespace HyperRendering::OpenGL33::Windows
{
	class CPlatformContext final : public IPlatformContext
	{
	public:
		virtual bool initialize(HyperPlatform::CWindow& window) override;
		virtual void shutdown() override;

		virtual void swap_buffers() const override;

	private:
		HyperPlatform::CWindow* m_window{ nullptr };

		HGLRC m_graphics_context{ nullptr };
	};
} // namespace HyperRendering::OpenGL33::Windows
