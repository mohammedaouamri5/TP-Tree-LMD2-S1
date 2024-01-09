workspace "TP"
    configurations { "Debug", "Release", "Dist" }
    platforms { "x86", "x86_64" }

project "TP"
    kind "ConsoleApp"
    language "C"
    targetdir ("bin/%{cfg.platform}_%{cfg.buildcfg}")
    objdir ("bin/obj/%{cfg.platform}_%{cfg.buildcfg}")

    files { "Source/**.h",  "Source/**.c" }

    toolset "gcc"

    filter "system:windows"
        systemversion "latest"
        defines { "WINDOWS" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        optimize "On"
        symbols "On"

    filter "configurations:Dist"
        defines { "DIST" }
        optimize "On"
        symbols "Off"

    filter "platforms:x86"
        architecture "x86"

    filter "platforms:x86_64"
        architecture "x86_64"
