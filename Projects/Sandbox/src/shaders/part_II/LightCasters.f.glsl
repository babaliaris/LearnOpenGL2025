#version 330 core

in vec3 fragPos;
in vec3 normal;
in vec2 texCoord;

out vec4 fColor;

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    int shininess;
};


struct Light
{
    //0 : Directional.
    //1 : Point.
    //2 : Spot.
    //3 : Ambient.
    int   type; 
    int   isFinal; // = 1 if it's the last light in the array.

    //The following can be unnitialized. Read "type"
    //to figure out if they are not! (It should be equal to -1).
    vec3  position;
    vec3  direction;
    vec3  color;
    float strength;
    float kc, kl, kq;
    float spotInner, spotOuter;
};

uniform Material uMat;
uniform Light uLights[10];
uniform vec3 uCamPos;

vec4 calculateFinalColor();

void main()
{
    fColor = calculateFinalColor();
}

vec4 calculateAmbient(in vec4 diffuseMap, in vec3 lightColor, float lightSrength)
{
    return vec4(vec3(diffuseMap) * lightColor * lightSrength, 1.0f);
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


vec4 calculateFinalColor()
{
    vec4 ambientColor   = vec4(0.0f);
    vec4 finalColor     = vec4(0.0f);
    vec4 diffuseMap     = texture(uMat.diffuse, texCoord);
    vec4 specularMap    = texture(uMat.specular, texCoord);
    vec3 normalDir      = normalize(normal);
    vec3 eyeDir         = normalize(fragPos - uCamPos);

    //For each light.
    for (int i = 0; i < 10; i++)
    {
        //Directional.
        if (uLights[i].type == 0)
        {   
            //Not implemented yet, return the normals as a debug break color.
            return vec4(normal, 1.0f);
        }

        //Point Or Spot Light.
        else if (uLights[i].type < 3)
        {
            float spotItense  = 1.0f;
            float lightDist   = length(fragPos - uLights[i].position);
            float attenuation = calcAttenuation(lightDist, uLights[i].kc, uLights[i].kl, uLights[i].kq);
            vec3  lightDir    = normalize(fragPos - uLights[i].position);

            //If it is also a spot light, add circle mode intensity.
            if (uLights[i].type == 2)
            {
                float theta = max( dot(-lightDir, -uLights[i].direction), 0.0f );
                spotItense  = clamp( (theta - uLights[i].spotOuter) / (uLights[i].spotInner - uLights[i].spotOuter), 0.0f, 1.0f);
            }

            //Calculating diffuse, specular and adding attenuation, is the same for both point and spot lights.
            vec4 diffuse  = calculateDiffuse(diffuseMap, uLights[i].color, uLights[i].strength, lightDir, normalDir);
            vec4 specular = calculateSpecular(specularMap, uLights[i].color, uLights[i].strength, lightDir, normalDir, eyeDir, uMat.shininess);

            finalColor  += (diffuse + specular) * attenuation * spotItense;
        }

        //Diffuse light.
        else if (uLights[i].type == 3)
        {   
            //Keep ambient total light in a seperate variable, because if it is the last
            //color added to the finalColor, then we make sure there is always some light!
            ambientColor += calculateAmbient(diffuseMap, uLights[i].color, uLights[i].strength);
        }

        //Break out of the loop if uLights[i] is the last light.
        if (uLights[i].isFinal == 1)
            break;
    }

    return clamp(finalColor + ambientColor, 0.0f, 1.0f);
}
