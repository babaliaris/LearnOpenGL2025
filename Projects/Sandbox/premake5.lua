project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    targetdir "%{_WORKING_DIR}/builds/%{cfg.shortname}/"
    objdir "%{_WORKING_DIR}/obj/%{prj.name}_%{cfg.shortname}/"
    targetname "sandbox"

    files
    {
        "src/**.h",
        "src/**.cpp",
        "src/**.hpp",
        "src/**.c"
    }

    includedirs
    {
        "%{_WORKING_DIR}/Extern/GLEW/include",
        "%{_WORKING_DIR}/Extern/GLFW/include",
        "%{_WORKING_DIR}/Projects/Framework/include"
    }

    links
    {
        "GLEW",
        "GLFW",
        "Framework"
    }

    filter "system:linux"
        pic "On"
        
        files
        {
        }

        defines
        {
        }

        links
        {
            "GL", "X11"
        }

    filter "system:windows"

        files
        {
        }

        defines 
        { 
        }

        links
        {
            "opengl32"
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
