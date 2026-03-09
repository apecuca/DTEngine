#version 330 core

out vec4 FragColor;

in vec2 texCoord;

uniform vec4 baseColor;
uniform sampler2D tex;

void main()
{
   FragColor = texture(tex, texCoord) * baseColor;
}