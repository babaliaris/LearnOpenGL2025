workspace "LearnOpenGL"
    configurations "debug"
    platforms "x64"
    startproject "Sandbox"

    group "Depedencies"
        include "Extern/GLEW"
        include "Extern/GLFW"
    group ""

    include "Projects/Sandbox"