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


struct PointLight
{
    vec3 color;
    vec3 pos;
    float strength;

    float kc;
    float kl;
    float kq;

};


struct SpotLight
{
    vec3 color;
    vec3 pos;
    vec3 direction;
    float strength;
    float inner;
    float outer;

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


//0=Directional, 1=Point Light, 2=Spot Light.
uniform int uChooseLight;

uniform Material uMat;
uniform AmbientLight uAmbient;
uniform PointLight uPointLight;
uniform SpotLight uSpotLight;
uniform vec3 uCamPos;


vec4 calculateAmbient(in vec4 diffuseMap);
vec4 calculateDiffuse(in vec4 diffuseMap, in vec3 lightColor, in float lightStrength, in vec3 lightDir, in vec3 normalDir);
vec4 calculateSpecular(in vec4 specularMap, in vec3 lightColor, in float lightStrength, in vec3 lightDir, in vec3 normalDir, in vec3 eyeDir, int shininess);
float calcAttenuation(in float d, in float kc, in float kl, in float kq);

void main()
{
    vec4 finalColor  = vec4(0.0f, 0.0f, 0.0f, 1.0f);

    vec4 diffuseMap  = texture(uMat.diffuse, texCoord);
    vec4 specularMap = texture(uMat.specular, texCoord);
    
    vec3 normalDir   = normalize(normal);
    vec3 eyeDir      = normalize(fragPos - uCamPos);

    vec3 lightColor;
    vec3 lightDir;
    float lightStrength;
    float lightDist;
    float kc, kl, kq;

    //Point Light.
    if (uChooseLight == 1)
    {
        lightColor      = uPointLight.color;
        lightStrength   = uPointLight.strength;
        lightDir        = normalize(fragPos - uPointLight.pos);
        lightDist       = length(fragPos - uPointLight.pos);
        kc              = uPointLight.kc;
        kl              = uPointLight.kl;
        kq              = uPointLight.kq;
    }

    //Spot Light.
    else if (uChooseLight == 2)
    {
        lightColor     = uSpotLight.color;
        lightStrength  = uSpotLight.strength;
        lightDir       = normalize(fragPos - uSpotLight.pos);
        lightDist      = length(fragPos - uSpotLight.pos);
        kc              = uSpotLight.kc;
        kl              = uSpotLight.kl;
        kq              = uSpotLight.kq;
    }

    //Debug color using normals.
    else
    {
        finalColor = vec4(normal, 1.0f);
    }

    //Calculate Phong Lighting.
    finalColor      += calculateDiffuse(diffuseMap, lightColor, lightStrength, lightDir, normalDir);
    finalColor      += calculateSpecular(specularMap, lightColor, lightStrength, lightDir, normalDir, eyeDir, uMat.shininess);
    finalColor      *= calcAttenuation(lightDist, kc, kl, kq);

    finalColor      += calculateAmbient(diffuseMap); //Add ambient at the end, to make sure there is some light.

    fColor = clamp(finalColor, 0.0f, 1.0f);
}

vec4 calculateAmbient(in vec4 diffuseMap)
{
    return vec4(vec3(diffuseMap) * uAmbient.color * uAmbient.strength, 1.0f);
}

vec4 calculateDiffuse(in vec4 diffuseMap, in vec3 lightColor, in float lightStrength, in vec3 lightDir, in vec3 normalDir)
{
    float diffStrength = max(dot(-lightDir, normalDir), 0.0f);

    return vec4(vec3(diffuseMap) * lightColor * lightStrength * diffStrength, 1.0f);
}


vec4 calculateSpecular(in vec4 specularMap, in vec3 lightColor, in float lightStrength, in vec3 lightDir, in vec3 normalDir, in vec3 eyeDir, int shininess)
{
    vec3 reflectDir = normalize(reflect(lightDir, normalDir));

    float specStrength = pow(max(dot(reflectDir, -eyeDir), 0.0f), shininess);

    return vec4( vec3(specularMap) * lightColor * lightStrength * specStrength, 1.0f);
}

float calcAttenuation(in float d, in float kc, in float kl, in float kq)
{
    return 1.0f/( kc + kl*d + kq*pow(d,2) );
}
