#version 330 core
layout (location=0) in vec3 vPos;
layout (location=1) in vec3 vNormal;
layout (location=2) in vec2 vTexCoord;

out vec3 fragPos;
out vec3 normal;
out vec2 texCoord;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;
uniform mat3 uNormal;

void main()
{
    fragPos     = vec3( uModel * vec4(vPos, 1.0f) );
    normal      = uNormal * vNormal;
    texCoord    = vTexCoord;
    gl_Position = uProj*uView*uModel*vec4(vPos, 1.0f);
}