#version 330

layout(location = 0) out vec4 colour;
in vec2 passTextureCoords;
uniform sampler2D renderedTexture;

void main()
{
    colour = texture(renderedTexture, passTextureCoords);
}
