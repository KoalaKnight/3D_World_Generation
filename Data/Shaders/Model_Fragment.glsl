#version 330

layout(location = 0) out vec4 colour;

in vec3 normals;
in vec3 fragPos;
in vec3 passColour;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    bool atteniation_b = false;

    vec3 lightColour = vec3(1.0f, 1.0f, 1.0f);
    vec3 objectColour = passColour;
    //Ambient Lighting
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColour;
    //Diffuse Lighting
    vec3 norm = normalize(normals);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * lightColour;
    //Specular Lighting
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0f), 32);
    vec3 specular = specularStrength * spec * lightColour;
    //Attenuation
    if(atteniation_b)
    {
        float scaleDistance = 0.2f;
        float distance = length(lightPos - fragPos) * scaleDistance;
        float attenuation = 1.0f / (distance * distance);
        diffuse *= attenuation;
        specular *= attenuation;
    }

    vec3 result = (ambient + diffuse + specular) * objectColour;
    //Gamma correction
    float gamma = 2.2;
    result.xyz = pow(result.xyz, vec3(1.0/gamma));

    colour = vec4(result, 1.0f);
}
