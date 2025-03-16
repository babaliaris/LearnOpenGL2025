#version 330 core

in vec4 color;
in vec2 texCoord;
out vec4 fColor;

uniform sampler2D uContainer;
uniform sampler2D uSmily;

void main()
{
    fColor = mix(texture(uContainer, texCoord) * color, texture(uSmily, texCoord), 0.2);
}