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
    includeDirs["Utils"] = "%{wks.location}/Examples/vendor/utils/src"
    includeDirs["spdlog"] = "%{wks.location}/Examples/vendor/utils/vendor/spdlog/include"
    includeDirs["effolkronium"] = "%{wks.location}/Examples/vendor/utils/vendor/effolkronium/include"
    
include "Quadtrees"
include "Examples/vendor/utils"
include "Examples"
