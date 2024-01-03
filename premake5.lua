workspace "Phoenix"
	architecture "x86_64"
	startproject "Sandbox"
	configurations { "Debug", "Release", "Dist" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["spdlog"] = "Phoenix/vendor/spdlog/include"
IncludeDir["GLFW"] = "Phoenix/vendor/GLFW/include"
IncludeDir["Glad"] = "Phoenix/vendor/Glad/include"
IncludeDir["ImGui"] = "Phoenix/vendor/imgui"
IncludeDir["glm"] = "Phoenix/vendor/glm"

group "Dependencies"
	include "Phoenix/vendor/GLFW"
	include "Phoenix/vendor/Glad"
	include "Phoenix/vendor/imgui"
group ""

project "Phoenix"
	kind "StaticLib"
	language "C++"
	location "Phoenix"
	staticruntime "on"
	cppdialect "Default"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	pchheader "pnpch.h"
	pchsource "Phoenix/src/pnpch.cpp"
	
	files { 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp" 
	}

	includedirs { 
		"%{IncludeDir.spdlog}",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links {
		"Glad",
		"ImGui",
		"GLFW",
		"opengl32.lib",
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"PN_PLATFORM_WINDOWS",
			"PN_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "PN_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PN_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "PN_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	location "Sandbox"
	cppdialect "Default"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

	includedirs { 
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}",
		"Phoenix/src"
	}

	links {
		"Phoenix",
		"ImGui"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"PN_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "PN_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PN_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "PN_DIST"
		runtime "Release"
		optimize "on"