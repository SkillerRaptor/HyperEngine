#include "HyperSystem/HyperWindows/WindowsPlatformUtils.hpp"

#include <GLFW/glfw3.h>

#ifdef HP_PLATFORM_WINDOWS
	#define GLFW_EXPOSE_NATIVE_WIN32
	#include <GLFW/glfw3native.h>
	#include <Windows.h>
#endif

#include "HyperCore/Application.hpp"

namespace HyperSystem
{
	std::optional<std::string> WindowsPlatformUtils::OpenFile(const char* filter)
	{
	#if defined(HP_PLATFORM_WINDOWS)
		OPENFILENAMEA ofn;
		CHAR szFile[260] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAMEA));
		ofn.lStructSize = sizeof(OPENFILENAMEA);
		ofn.hwndOwner = glfwGetWin32Window(HyperCore::Application::Get()->GetWindow()->GetContext()->GetWindow());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
		if (GetOpenFileNameA(&ofn) == TRUE)
			return ofn.lpstrFile;
	#endif
		return std::nullopt;
	}

	std::optional<std::string> WindowsPlatformUtils::SaveFile(const char* filter)
	{
	#if defined(HP_PLATFORM_WINDOWS)
		OPENFILENAMEA ofn;
		CHAR szFile[260] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAMEA));
		ofn.lStructSize = sizeof(OPENFILENAMEA);
		ofn.hwndOwner = glfwGetWin32Window(HyperCore::Application::Get()->GetWindow()->GetContext()->GetWindow());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
		if (GetSaveFileNameA(&ofn) == TRUE)
			return ofn.lpstrFile;
	#endif
		return std::nullopt;
	}
}