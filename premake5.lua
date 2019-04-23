workspace "NightFall"
	architecture "x64"
	startproject "TestApp"
	
	configurations {
		"Debug",
		"Release",
		"Dist"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["spdlog"] = "NightFall/vendor/spdlog/include"
IncludeDir["GLFW"] = "NightFall/vendor/GLFW/include"
IncludeDir["Glad"] = "NightFall/vendor/glad/include"
IncludeDir["ImGui"] = "NightFall/vendor/ImGui"

include "NightFall/vendor/GLFW"
include "NightFall/vendor/glad"
include "NightFall/vendor/ImGui"

project "NightFall"
	location "NightFall"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}
	links
	{
		"GLFW",
		"Glad"
	}
	filter "system:windows"
		systemversion "latest"
		
		defines
		{
			"PLATFORM_WINDOWS"
		}
	filter "configurations:Debug"
		defines "DEBUG"
		symbols "on"
		runtime "Debug"

	filter "configurations:Release"
		defines "RELEASE"
		optimize "on"
		runtime "Release"

	filter "configurations:Dist"
		defines "DIST"
		optimize "on"
		runtime "Release"

project "TestApp"
	location "TestApp"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	includedirs
	{
		"%{prj.name}/src",
		"NightFall/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}
	links
	{
		"NightFall"
	}
	
	filter "system:windows"
		systemversion "latest"
		
		defines
		{
			"PLATFORM_WINDOWS"
		}
	filter "configurations:Debug"
		defines "DEBUG"
		symbols "on"
		runtime "Debug"

	filter "configurations:Release"
		defines "RELEASE"
		optimize "on"
		runtime "Release"

	filter "configurations:Dist"
		defines "DIST"
		optimize "on"
		runtime "Release"