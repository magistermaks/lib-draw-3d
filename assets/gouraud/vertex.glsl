#version 330 core

struct Material {
	sampler2D specular;
	sampler2D emissive; // unused
	float shininess;
};

struct Light {
	vec3 color;
	vec3 source;
};

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_normal;
layout (location = 2) in vec2 vertex_uv;

out vec3 light_color;
out vec2 uv;

uniform vec3 camera;
uniform sampler2D sampler;

uniform mat4 view_projection_mat;
uniform mat4 model_mat;
uniform mat3 normal_mat;

uniform Material material;
uniform Light light;

void main()
{
	vec3 position = vec3(model_mat * vec4(vertex_position, 1.0));
    vec3 normal = normalize(normal_mat * vertex_normal);

    gl_Position = view_projection_mat * vec4(position, 1.0);
    
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

    light_color = ambient + diffuse + specular;
	uv = vertex_uv;	
}


