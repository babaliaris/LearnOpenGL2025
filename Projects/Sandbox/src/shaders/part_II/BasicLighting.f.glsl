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
uniform vec3 uCamPos;


vec4 calculateAmbient();
vec4 calculateDiffuse(in vec3 lightDir, in vec3 normalDir);
vec4 calculateSpecular(in vec3 lightDir, in vec3 normalDir, in vec3 eyeDir);

void main()
{
    vec3 lightDir   = normalize(fragPos - uLight.pos);
    vec3 normalDir  = normalize(normal);
    vec3 eyeDir     = normalize(fragPos - uCamPos);

    vec4 texture = texture(uContainer, texCoord);

    vec4 phongLight = calculateAmbient() + calculateDiffuse(lightDir, normalDir);
    phongLight      = phongLight + calculateSpecular(lightDir, normalDir, eyeDir);

    fColor = texture * phongLight;
}

vec4 calculateAmbient()
{
    return vec4(uAmbient.color * uAmbient.strength, 1.0f);
}

vec4 calculateDiffuse(in vec3 lightDir, in vec3 normalDir)
{
    float diffStrength = max(dot(-lightDir, normalDir), 0.0f);

    return vec4(uLight.color * uLight.strength * diffStrength, 1.0f);
}


vec4 calculateSpecular(in vec3 lightDir, in vec3 normalDir, in vec3 eyeDir)
{
    vec3 reflectDir = normalize(reflect(lightDir, normalDir));

    float specStrength = pow(max(dot(reflectDir, -eyeDir), 0.0f), 32);

    return vec4(uLight.color * uLight.strength * specStrength, 1.0f);
}
