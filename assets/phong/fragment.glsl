#version 330 core

struct Material {
	sampler2D specular;
	sampler2D emissive;
	float shininess;
};

struct Light {
	vec3 color;
	vec3 source;
};

out vec4 color;

in vec3 normal;  
in vec3 position;  
in vec2 uv;
  
uniform vec3 camera;
uniform sampler2D sampler;
uniform Material material;
uniform Light light;

void main() {

	vec3 emission = texture(material.emissive, uv).rgb;

    // ambient light
    vec3 ambient = 0.15f * light.color;
  	
	// diffuse light
	vec3 light_direction = normalize(light.source - position);
	float diff = max(dot(normal, light_direction), 0.0f);
	vec3 diffuse = diff * light.color;
    
	// specular light
	vec3 view_direction = normalize(camera - position);
	vec3 reflect_direction = reflect(-light_direction, normal);
	float spec = pow(max(dot(view_direction, reflect_direction), 0.0), material.shininess);
	vec3 specular = texture(material.specular, uv).rgb * spec * light.color;
        
    color = vec4((ambient + diffuse + specular + emission) * texture(sampler, uv).rgb, 1.0);
}
