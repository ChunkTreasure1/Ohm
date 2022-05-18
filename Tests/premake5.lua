outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Tests"
	location "."
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"

	targetdir ("../bin/" .. outputdir .."/%{prj.name}")
	objdir ("../bin-int/" .. outputdir .."/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp",
		"src/**.hpp",
	}

	includedirs
	{
		"../Ohm/src",
		"src",
		"$(VCInstallDir)UnitTest/include"
	}

	libdirs
	{
		"$(VCInstallDir)UnitTest/lib"
	}

	filter "system:windows"
		systemversion "latest"

		filter "configurations:Debug"
			defines { "OHM_DEBUG" }
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			runtime "Release"
			optimize "on"

		filter "configurations:Dist"
			defines { "OHM_DIST", "NDEBUG" }
			runtime "Release"
			optimize "on"