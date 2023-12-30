workspace "Amber"
	architecture "x64"

	configurations{
	"Debug",
	"Release",
	"Dist"
	}

	startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Amber/vendor/GLFW/include"
IncludeDir["Glad"] = "Amber/vendor/Glad/include"
IncludeDir["ImGui"] = "Amber/vendor/imgui"
IncludeDir["glm"] = "Amber/vendor/glm"

include "Amber/vendor/GLFW"
include "Amber/vendor/Glad"
include "Amber/vendor/imgui"

project "Amber"
	location "Amber"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "precHeaders.h"
	pchsource "Amber/src/precHeaders.cpp"

	files{ 
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
		}

	includedirs{ 
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
		systemversion "latest"

		defines { 
		"AM_PLATFORM_WINDOWS", 
		"AM_BUILD_DLL",
		"GLFW_INCLUDE_NONE"
		}
 
	filter "configurations:Debug"
		defines "AM_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "AM_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "AM_DIST"
		runtime "Release"
		optimize "on"
		 

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17" 
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files{ 
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp" 
	}

	includedirs { 
		"Amber/vendor/spdlog/include",
		"Amber/src",
		"Amber/vendor",
		"%{IncludeDir.glm}"
	}

	links {
		"Amber"
	}

	filter "system:windows" 
		systemversion "latest"

		defines {  "AM_PLATFORM_WINDOWS"  } 

	filter "configurations:Debug"
		defines "AM_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "AM_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "AM_DIST"
		runtime "Release"
		optimize "on"