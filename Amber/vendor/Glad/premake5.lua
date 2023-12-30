project "Glad"
	kind "StaticLib"
	staticruntime "on" 
	language "C"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c"
	}
 
	includedirs{
		"include"
	}

	filter "system:windows" 
 		systemversion "latest"
		
	filter "configurations:Debug"
		defines "AM_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "AM_RELEASE"
		runtime "Release"
		optimize "on"
 