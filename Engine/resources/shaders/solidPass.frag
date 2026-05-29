#version 430 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D tex;
uniform vec4 color;

void main()
{
    float alpha = texture(tex, TexCoord).a * color.a;
    FragColor = vec4(alpha, 0.0, 0.0, 1.0);
}