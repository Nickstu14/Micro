workspace "Micro"
	architecture "x64"
	startproject "SandBox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Micro/vendor/glfw/include"
IncludeDir["Glad"] = "Micro/vendor/Glad/include"
IncludeDir["ImGui"] = "Micro/vendor/imgui"
IncludeDir["glm"] = "Micro/vendor/glm"


include "Micro/vendor"
include "Micro/vendor/Glad"


project "Micro"
	location "Micro"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "Mipch.h"
	pchsource "Micro/src/Mipch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"MC_PLATFORM_WINDOWS",
			"MC_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"_WINDLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/SandBox")
		}

		filter "configurations:Debug"
			defines "MC_DEBUG"
			runtime "Debug"
			symbols "On"

		filter "configurations:Release"
			defines "MC_RELEASE"
			runtime "Release"
			optimize "On"

		filter "configurations:Dist"
			defines "MC_DIST"
			runtime "Release"
			optimize "On"


project "SandBox"
	location "SandBox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Micro/vendor/spdlog/include",
		"Micro/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Micro"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"MC_PLATFORM_WINDOWS"
		}


	filter "configurations:Debug"
		defines "MC_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "MC_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "MC_DIST"
		runtime "Release"
		optimize "On"