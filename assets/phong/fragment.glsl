#version 460 core

#require ../common/light.glsl

out vec4 color;

in vec3 normal;  
in vec3 position;  
in vec2 uv;

uniform int light_count = 2;
uniform vec3 camera;
uniform sampler2D sampler;
uniform Material material;

layout (std430, binding = 0) buffer lights_buffer {
	Light lights[];
};

void main() {

	vec3 specular = texture(material.specular, uv).rgb;
	vec3 light = texture(material.emissive, uv).rgb;

	for( int i = 0; i < lights.length(); i ++ ) {
		light += getLight(lights[i], specular, normal, position, camera, material.shininess);
	}
        
    color = vec4(light * texture(sampler, uv).rgb, 1.0);
}

