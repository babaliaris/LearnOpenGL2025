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


struct SpotLight
{
    vec3 color;
    vec3 pos;
    float strength;

    float kc;
    float kl;
    float kq;

};

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    int shininess;
};


uniform Material uMat;
uniform AmbientLight uAmbient;
uniform SpotLight uSpotLight;
uniform vec3 uCamPos;


vec4 calculateAmbient(in vec4 diffuseMap);
vec4 calculateDiffuse(in vec4 diffuseMap, in vec3 lightDir, in vec3 normalDir);
vec4 calculateSpecular(in vec4 specularMap, in vec3 lightDir, in vec3 normalDir, in vec3 eyeDir, int shininess);
float calcAttenuation(in float d, in float kc, in float kl, in float kq);

void main()
{
    vec3 lightDir   = normalize(fragPos - uSpotLight.pos);
    vec3 normalDir  = normalize(normal);
    vec3 eyeDir     = normalize(fragPos - uCamPos);

    float lightDist = length(fragPos - uSpotLight.pos);

    vec4 diffuseMap  = texture(uMat.diffuse, texCoord);
    vec4 specularMap = texture(uMat.specular, texCoord);

    vec4 finalColor  = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    finalColor      += calculateDiffuse(diffuseMap, lightDir, normalDir);
    finalColor      += calculateSpecular(specularMap, lightDir, normalDir, eyeDir, uMat.shininess);
    finalColor      *= calcAttenuation(lightDist, uSpotLight.kc, uSpotLight.kl, uSpotLight.kq);

    finalColor      += calculateAmbient(diffuseMap); //Add ambient at the end, to make sure there is some light.

    fColor = clamp(finalColor, 0.0f, 1.0f);
}

vec4 calculateAmbient(in vec4 diffuseMap)
{
    return vec4(vec3(diffuseMap) * uAmbient.color * uAmbient.strength, 1.0f);
}

vec4 calculateDiffuse(in vec4 diffuseMap, in vec3 lightDir, in vec3 normalDir)
{
    float diffStrength = max(dot(-lightDir, normalDir), 0.0f);

    return vec4(vec3(diffuseMap) * uSpotLight.color * uSpotLight.strength * diffStrength, 1.0f);
}


vec4 calculateSpecular(in vec4 specularMap, in vec3 lightDir, in vec3 normalDir, in vec3 eyeDir, int shininess)
{
    vec3 reflectDir = normalize(reflect(lightDir, normalDir));

    float specStrength = pow(max(dot(reflectDir, -eyeDir), 0.0f), shininess);

    return vec4( vec3(specularMap) * uSpotLight.color * uSpotLight.strength * specStrength, 1.0f);
}

float calcAttenuation(in float d, in float kc, in float kl, in float kq)
{
    return 1.0f/( kc + kl*d + kq*pow(d,2) );
}
