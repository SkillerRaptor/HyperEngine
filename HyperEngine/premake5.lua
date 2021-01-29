project "HyperEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "c++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{ 
		"src/**.cpp",
		"src/**.hpp",
		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp"
	}
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"src",
		"src/Hyperion",
		"%{IncludeDir.fmt}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.json}",
		"%{IncludeDir.rttr}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.vulkan}"
	}

	libdirs
	{
		"%{LibDir.vulkan}"
	}

	links
	{
		"fmt",
		"Glad",
		"glfw",
		"glm",
		"ImGui",
		"ImGuizmo",
		"json",
		"rttr",
		"vulkan",
		"vulkan-1.lib"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "HP_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HP_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HP_DIST"
		runtime "Release"
		optimize "on"
