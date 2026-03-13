#version 430 core

// Color output
out vec4 FragColor;

// In from Vertex
in vec2 TexCoords;

// Uniforms
uniform sampler2D screenTexture;
uniform int screenWidth;
uniform int screenHeight;

void main()
{
    FragColor = texture(screenTexture, TexCoords);
}