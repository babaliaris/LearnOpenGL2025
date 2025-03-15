workspace "LearnOpenGL"
    configurations "debug"
    platforms "x64"
    startproject "Sandbox"

    group "Depedencies"
        include "Extern/GLEW"
        include "Extern/GLFW"
        include "Projects/STB_IMAGE"
        include "Projects/Framework"
    group ""

    include "Projects/Sandbox"