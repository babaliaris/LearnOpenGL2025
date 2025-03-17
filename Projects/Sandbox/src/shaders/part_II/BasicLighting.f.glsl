#version 330 core

in vec3 fragPos;
in vec3 normal;
in vec2 texCoord;

out vec4 fColor;

struct AmbientLight
{
    vec3 color;
    float strength;

};


struct LightSource
{
    vec3 color;
    vec3 pos;
    float strength;

};


uniform sampler2D uContainer;
uniform AmbientLight uAmbient;
uniform LightSource uLight;


vec4 calculateAmbient();

void main()
{
    vec4 texture = texture(uContainer, texCoord);

    fColor = texture * calculateAmbient();
}

vec4 calculateAmbient()
{
    return vec4(uAmbient.color * uAmbient.strength, 1.0f);
}
