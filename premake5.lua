workspace "Raven"
	architecture "x86_64"
	startproject "TestApp"
	
	configurations {
		"Debug",
		"Release",
		"Dist"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["spdlog"] = "Raven/vendor/spdlog/include"
IncludeDir["GLFW"] = "Raven/vendor/GLFW/include"
IncludeDir["Glad"] = "Raven/vendor/glad/include"
IncludeDir["ImGui"] = "Raven/vendor/ImGui"
IncludeDir["glm"] = "Raven/vendor/glm/glm"
IncludeDir["stb_image"] = "Raven/vendor/stb_image"
IncludeDir["RavenLib"] = "RavenLib/src/"

group "Dependencies"
	include "Raven/vendor/GLFW"
	include "Raven/vendor/glad"
	include "Raven/vendor/ImGui"	

group ""

project "Raven"
	location "Raven"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "pch.h"
	pchsource "Raven/src/pch.cpp"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}
	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.RavenLib}"
	}
	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"RavenLib"
	}
	filter "system:windows"
		systemversion "latest"
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
project "RavenLib"
	location "RavenLib"
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
		"Raven/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
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
		"Raven/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.RavenLib}"
	}
	links
	{
		"Raven"
	}
	
	filter "system:windows"
		systemversion "latest"
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