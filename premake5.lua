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


include "Micro/vendor"
include "Micro/vendor/Glad"


project "Micro"
	location "Micro"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "Mipch.h"
	pchsource "Micro/src/Mipch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}"
	}

	links{
		"GLFW",
		"Glad",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
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
			buildoptions "/MDd"
			symbols "On"

		filter "configurations:Release"
			defines "MC_RELEASE"
			runtime "Release"
			buildoptions "/MD"
			optimize "On"

		filter "configurations:Dist"
			defines "MC_DIST"
			runtime "Release"
			buildoptions "/MD"
			optimize "On"


project "SandBox"
	location "SandBox"
	kind "ConsoleApp"
	language "C++"

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
		"Micro/src"
	}

	links
	{
		"Micro"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MC_PLATFORM_WINDOWS"
		}


	filter "configurations:Debug"
		defines "MC_DEBUG"
		runtime "Debug"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "MC_RELEASE"
		runtime "Release"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "MC_DIST"
		runtime "Release"
		buildoptions "/MD"
		optimize "On"