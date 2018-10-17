#version 330

layout (location = 0) in vec3 inVertexPosition;
layout (location = 1) in vec3 inNormals;
layout (location = 2) in vec2 inTextureCoords;

out vec3 normals;
out vec3 fragPos;
out vec4 clipSpace;
out vec2 textureCoords;
out vec3 toCameraVector;
out vec3 fromLightVector;

uniform vec3 viewPos;
uniform vec3 lightPos;

uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 projMatrix;

void main()
{
    vec4 worldPosition = modelMatrix * vec4(inVertexPosition.x, inVertexPosition.y, inVertexPosition.z, 1.0);
    clipSpace = projMatrix * viewMatrix * worldPosition;
    gl_Position = clipSpace;
    fragPos = vec3(modelMatrix * vec4(inVertexPosition, 1.0));
    normals = mat3(transpose(inverse(modelMatrix))) * inNormals;
    textureCoords = inTextureCoords * 24.0;
    toCameraVector = viewPos - worldPosition.xyz;
    fromLightVector  = worldPosition.xyz - lightPos;
}
