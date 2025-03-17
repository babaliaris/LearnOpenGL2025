#version 330 core

in vec2 texCoord;
out vec4 fColor;

uniform sampler2D uContainer;
uniform vec3 uLightColor;

void main()
{
    fColor = texture(uContainer, texCoord) * vec4(uLightColor, 1.0f);
}