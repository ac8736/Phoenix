workspace "Phoenix"
	architecture "x86_64"
	startproject "Sandbox"
	configurations { "Debug", "Release", "Dist" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Phoenix"
	kind "SharedLib"
	language "C++"
	location "Phoenix"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

	includedirs { 
		"%{prj.name}/vendor/spdlog/include"
	}

	postbuildcommands { ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox") }

	filter "system:windows"
		cppdialect "Default"
		staticruntime "On"
		systemversion "latest"

		defines {
			"PN_PLATFORM_WINDOWS",
			"PN_BUILD_DLL"
		}

	filter "configurations:Debug"
		defines "PN_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "PN_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "PN_DIST"
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
		symbols "On"

	filter "configurations:Release"
		defines "PN_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "PN_DIST"
		optimize "On"