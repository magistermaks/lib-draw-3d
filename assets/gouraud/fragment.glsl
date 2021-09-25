#version 330 core

out vec4 color;

in vec3 light_color;
in vec2 uv;

uniform sampler2D sampler;

void main() {
   color = vec4(light_color * texture(sampler, uv).rgb, 1.0);
}
