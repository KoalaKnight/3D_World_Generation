#version 330

layout (location = 0) in vec3 inVertexPosition;

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
}
