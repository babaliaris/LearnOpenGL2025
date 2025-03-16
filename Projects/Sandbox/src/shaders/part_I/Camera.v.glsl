#version 330 core
layout (location=0) in vec3 vPos;
layout (location=1) in vec2 vTexCoord;

out vec2 texCoord;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

void main()
{
    texCoord = vTexCoord;
    gl_Position = uProj*uView*uModel*vec4(vPos, 1.0f);
}