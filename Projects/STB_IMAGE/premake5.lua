project "STB_IMAGE"
    kind "StaticLib"
    language "C++"
    targetdir "%{_WORKING_DIR}/builds/%{cfg.shortname}/"
    objdir "%{_WORKING_DIR}/obj/%{prj.name}_%{cfg.shortname}/"

    files
    {
        "src/stb_image.cpp",
        "%{_WORKING_DIR}/Extern/stb_image.h"
    }

    includedirs
    {
        "src",
        "%{_WORKING_DIR}/Extern/STB"
    }


    --All Platforms.
    filter{}
    
    filter "configurations:debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:dist"
        runtime "Release"
        optimize "on"

    filter "configurations:release"
        runtime "Release"
        optimize "on"
