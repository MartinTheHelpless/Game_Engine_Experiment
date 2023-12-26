workspace "Amber"
	architecture "x64"

	configurations{
	"Debug",
	"Release",
	"Dist"
	}


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Amber/vendor/GLFW/include"

include "Amber/vendor/GLFW"

project "Amber"
	location "Amber"
	kind "SharedLib"
	language "C++"

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
		"%{IncludeDir.GLFW}"
		}

	links{
		"GLFW",
		"opengl32.lib"
		}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines { 
		"AM_PLATFORM_WINDOWS", 
		"AM_BUILD_DLL" 
		}

		postbuildcommands{ 
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
 			}

	filter "configurations:Debug"
		defines "AM_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "AM_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "AM_DIST"
		symbols "On"
		 

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files{ 
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp" 
	}

	includedirs { 
		"Amber/vendor/spdlog/include",
		"Amber/src"
	}

	links {
		"Amber"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {  "AM_PLATFORM_WINDOWS"  } 

	filter "configurations:Debug"
		defines "AM_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "AM_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "AM_DIST"
		symbols "On"