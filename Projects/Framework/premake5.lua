project "Framework"
    kind "StaticLib"
    language "C++"
    targetdir "%{_WORKING_DIR}/builds/%{cfg.shortname}/"
    objdir "%{_WORKING_DIR}/obj/%{prj.name}_%{cfg.shortname}/"

    files
    {
        "src/**.h",
        "src/**.cpp",
        "src/**.hpp",
        "src/**.c",
        "include/**.h"
    }

    includedirs
    {
        "include",
        "%{_WORKING_DIR}/Extern/GLEW/include",
        "%{_WORKING_DIR}/Extern/GLFW/include",
        "%{_WORKING_DIR}/Extern/GLM",
        "%{_WORKING_DIR}/Extern/STB",
        "%{_WORKING_DIR}/Extern/assimp/include",
        "%{_WORKING_DIR}/Extern/assimp/build/include"
    }

    prebuildcommands {
        -- Compile Assimp.
        "{MKDIR} %{_WORKING_DIR}/Extern/assimp/build",
        "{CHDIR} %{_WORKING_DIR}/Extern/assimp/build && cmake .. -DBUILD_SHARED_LIBS=OFF && make",
        "{COPYFILE} %{_WORKING_DIR}/Extern/assimp/build/lib/libassimp.a %{_WORKING_DIR}/builds/%{cfg.shortname}"
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
