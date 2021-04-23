project "Quadtrees"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    architecture ("x86_64")    
    staticruntime "on"
    
    objdir (outputBinInt)
    targetdir (outputBin)

    includedirs
    {
        "%{prj.location}/src"
    }
    files
    {
        "src/**.cpp",
        "src/**.h"        
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"