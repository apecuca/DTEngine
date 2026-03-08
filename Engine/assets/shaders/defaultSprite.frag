#version 330 core

out vec4 FragColor;

uniform vec4 baseColor;

void main()
{
   vec4 outColor = baseColor;
   FragColor = outColor;
}