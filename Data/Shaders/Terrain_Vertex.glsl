#version 330

layout (location = 0) in vec3 inVertexPosition;
layout (location = 1) in vec3 inNormals;
layout (location = 2) in vec2 inTextureCoords;

out vec3 normals;
out vec3 fragPos;
out vec2 passTextureCoords;

uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 projMatrix;
uniform vec4 plane;

void main()
{
    gl_ClipDistance[0] = dot(modelMatrix * vec4(inVertexPosition.x, inVertexPosition.y, inVertexPosition.z, 1.0), plane);
    gl_Position = projMatrix * viewMatrix * modelMatrix *
                   vec4(inVertexPosition.x,
                        inVertexPosition.y,
                        inVertexPosition.z,
                        1.0);
    fragPos = vec3(modelMatrix * vec4(inVertexPosition, 1.0));
    normals = mat3(transpose(inverse(modelMatrix))) * inNormals;
    passTextureCoords = inTextureCoords;
}
