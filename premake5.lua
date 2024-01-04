workspace "TP"
    configurations { "Debug", "Release", "Dist" }
    
    project "TP"
        kind "ConsoleApp"
        language "C"
        targetdir ("bin/%{cfg.buildcfg}")
        objdir ("bin/obj/%{cfg.buildcfg}")
        buildlog "LOG/%{cfg.buildcfg}/TP.log" 
    
        files { "Source/**.h", "Source/**.c" }

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
