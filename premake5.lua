workspace "Phoenix"
	architecture "x86_64"
	startproject "Sandbox"
	configurations { "Debug", "Release", "Dist" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
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
	kind "SharedLib"
	language "C++"
	location "Phoenix"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	pchheader "pnpch.h"
	pchsource "Phoenix/src/pnpch.cpp"
	
	files { 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp" 
	}

	includedirs { 
		"%{prj.name}/vendor/spdlog/include",
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

	postbuildcommands { ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"") }

	filter "system:windows"
		cppdialect "Default"
		staticruntime "On"
		systemversion "latest"

		defines {
			"PN_PLATFORM_WINDOWS",
			"PN_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "PN_DEBUG"
		staticruntime "off"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "PN_RELEASE"
		staticruntime "off"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "PN_DIST"
		staticruntime "off"
		runtime "Release"
		optimize "On"

project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	location "Sandbox"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

	includedirs { 
		"Phoenix/vendor/spdlog/include",
		"%{IncludeDir.glm}",
		"Phoenix/src"
	}

	links {
		"Phoenix"
	}

	filter "system:windows"
		cppdialect "Default"
		staticruntime "On"
		systemversion "latest"

		defines {
			"PN_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "PN_DEBUG"
		staticruntime "off"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "PN_RELEASE"
		staticruntime "off"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "PN_DIST"
		staticruntime "off"
		runtime "Release"
		optimize "On"