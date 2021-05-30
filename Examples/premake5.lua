project "Examples"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    architecture ("x86_64")
    staticruntime "on"
    
    objdir (outputBinInt)
    targetdir (outputBin)

    files
    {
        "src/**.cpp",
        "src/**.h"
    }
    
    includedirs 
    {
        includeDirs["Quadtrees"]
    }
    
    links 
    {
        "Quadtrees"
    }
    
    filter "system:windows"
		systemversion "latest"

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        runtime "Release"
        optimize "On"

    