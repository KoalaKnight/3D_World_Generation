#version 330

layout(location = 0) out vec4 colour;

in vec4 clipSpace;
in vec3 normals;
in vec3 fragPos;
in vec2 textureCoords;
in vec3 toCameraVector;
in vec3 fromLightVector;

uniform float moveFactor;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform sampler2D dudvMap;
uniform sampler2D normalMap;
uniform sampler2D depthMap;

const float waveStrength = 0.02;
const float shineDamper = 20.0;
const float reflectivity = 0.6;

/*
        BLACK ARTIFACTS CAUSED BY DARK INSIDE OF TERRAIN SLICE USED FOR REFLECTION TEXTURE
*/
void main()
{
    vec3 lightColour = vec3(1.0f, 1.0f, 1.0f);
    vec2 ssc = ((clipSpace.xy/clipSpace.w)/2.0) + 0.5;
    vec2 refractTexCoords = vec2 (ssc.x, ssc.y);
    vec2 reflectTexCoords = vec2 (ssc.x, 1-ssc.y);
    float near = 0.001f;
    float far = 1000.0f;
    float depth = texture(depthMap, refractTexCoords).r;
    float floorDistance = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));

    depth = gl_FragCoord.z;
    float waterDistance = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));

    float waterDepth = floorDistance - waterDistance;

    vec2 distortedTexCoords = texture(dudvMap, vec2(textureCoords.x + moveFactor, textureCoords.y)).rg*0.1;
	distortedTexCoords = textureCoords + vec2(distortedTexCoords.x, distortedTexCoords.y+moveFactor);
	vec2 totalDistortion = (texture(dudvMap, distortedTexCoords).rg * 2.0 - 1.0) * waveStrength * clamp(waterDepth / 1.7, 0.0, 1.0);


    refractTexCoords += totalDistortion;
    refractTexCoords = clamp(refractTexCoords, 0.001, 0.999);

    reflectTexCoords += totalDistortion;
    reflectTexCoords.x = clamp(reflectTexCoords.x, 0.001, 0.999);
    reflectTexCoords.y = clamp(reflectTexCoords.y, 0.001, 0.999);

    vec4 reflectColour = texture(reflectionTexture, reflectTexCoords);
    vec4 refractColour = texture(refractionTexture, refractTexCoords);

    vec4 normalMapColour = texture(normalMap, distortedTexCoords);
    vec3 normal = vec3((normalMapColour.r * 2.0) - 1.0, normalMapColour.b * 3.0, (normalMapColour.g * 2.0) - 1.0);
    normal = normalize(normal);
    //normal.y = clamp(normal.y, 0.001, 0.999);

    vec3 viewVector = normalize(toCameraVector);
    float  refractiveFactor = dot(viewVector, normal);
    refractiveFactor = pow(refractiveFactor, 1.0);
    //refractiveFactor = clamp(refractiveFactor, 0.01, 0.99);

    vec3 reflectedLight = reflect(normalize(fromLightVector), normal);
	float specular = max(dot(reflectedLight, viewVector), 0.0);
	specular = pow(specular, shineDamper);
	vec3 specularHighlights = lightColour * specular * reflectivity * clamp(waterDepth / 0.1, 0.0, 1.0);

    vec4 blue = vec4(0.0, 0.0, 1.0, 1.0);
    //colour = reflectColour;
    colour = mix(reflectColour, refractColour, refractiveFactor);
    colour = mix(colour, blue, 0.2) + vec4(specularHighlights, 0.0);
    colour.a = clamp(waterDepth / 0.1, 0.0, 1.0);

    /*bool atteniation_b = false;

    vec3 lightColour = vec3(1.0f, 1.0f, 1.0f);
    vec3 objectColour = vec3(0.0f, 0.0f, 1.0f);
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

    colour = vec4(result, 1.0f);*/
}
