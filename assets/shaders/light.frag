#version 460 core
in vec3 normal;
in vec3 frag_pos;
in vec2 texture_coordinate;

out vec4 FragColor;

struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;
uniform vec3 cam_pos;
uniform vec3 object_colour;
uniform vec3 light_colour;
uniform sampler2D texture_diffuse;


void main(){
    //ambient
    vec3 ambient = light.ambient * material.ambient;

    //diffuse
    vec3 norm = normalize(normal);
    vec3 light_dir = normalize(light.position - frag_pos);
    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    //specular
    vec3 view_dir = normalize(cam_pos - frag_pos); 
    vec3 reflect_dir = reflect(-light_dir, norm);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);

    vec3 result = ambient + diffuse + specular;
    //FragColor = vec4(result, 1.0);
    FragColor = texture(texture_diffuse, texture_coordinate);
}
