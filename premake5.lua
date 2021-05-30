workspace "Quadtrees"
    architecture "x86_64"

    configurations {"Debug","Release"}
    flags
	{
		"MultiProcessorCompile"
	}
    
    outputBin = "%{wks.location}/bin/%{cfg.buildcfg}-%{cfg.architecture}/%{prj.name}"
    outputBinInt = "%{wks.location}/bin-int/%{cfg.buildcfg}-%{cfg.architecture}/%{prj.name}"
    
    includeDirs= {}
    includeDirs["Quadtrees"] = "%{wks.location}/Quadtrees/src"
    
include "Quadtrees"
include "Examples"
