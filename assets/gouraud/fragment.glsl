#version 330 core

out vec4 FragColor;

in vec3 LightingColor;
in vec2 Uv;

uniform sampler2D sampler;

void main()
{
   FragColor = vec4(LightingColor * texture(sampler, Uv).xyz, 1.0);
}
