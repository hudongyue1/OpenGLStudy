#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 FragColor;

struct Material {
    sampler2D diffuse;
//     vec3 diffuse;
    sampler2D specular;
    float shininess;
};

// point light and distance light
// struct Light {
//     vec4 DirOrPos;
//
//     vec3 ambient;
//     vec3 diffuse;
//     vec3 specular;
//
//     float constant;
//     float linear;
//     float quadratic;
// };

// spot light
struct Light {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;

uniform vec3 viewPosition;

// point light and distance light
// void main() {
//     // ambient
//     vec3 ambient = vec3(texture(material.diffuse, TexCoords)) * light.ambient;
//
//     // diffuse
//     vec3 norm = normalize(Normal);
//     vec3 lightDir;
//     if(light.DirOrPos.w == 0.0) {
//         lightDir = normalize(-light.DirOrPos.xyz);
//     } else if(light.DirOrPos.w == 1.0) {
//         lightDir = normalize(light.DirOrPos.xyz - FragPos);
//     }
//     float diff = max(dot(norm, lightDir), 0.0f);
//     vec3 diffuse = diff * vec3(texture(material.diffuse, TexCoords)) * light.diffuse;
//
//     // specular
//     vec3 viewDir = normalize(viewPosition - FragPos);
//     vec3 reflectDir = reflect(-lightDir, norm);
//     float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//     vec3 specular = spec * vec3(texture(material.specular, TexCoords)) * light.specular;
//
//     // calculate attenuation
//     float attenuation;
//     if(light.DirOrPos.w == 0.0) {
//         attenuation = 1.0f;
//     } else if(light.DirOrPos.w == 1.0) {
//         float distance = length(light.DirOrPos.xyz - FragPos);
//         attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
//     }
//
// //     FragColor =  vec4(ambient + diffuse + specular, 1.0);
//     FragColor =  vec4((ambient + diffuse + specular) * attenuation, 1.0);
//
// }

// point light and distance light
void main() {
    // ambient
    vec3 ambient = vec3(texture(material.diffuse, TexCoords)) * light.ambient;
    vec3 diffuse = vec3(0.0f, 0.0f, 0.0f);
    vec3 specular = vec3(0.0f, 0.0f, 0.0f);

    vec3 lightDir = normalize(light.position - FragPos);
    // calculate angle
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);

    if(theta > light.outerCutOff) {
        // diffuse
        vec3 norm = normalize(Normal);
        float diff = max(dot(norm, lightDir), 0.0f);
        diffuse = diff * vec3(texture(material.diffuse, TexCoords)) * light.diffuse;

        // specular
        vec3 viewDir = normalize(viewPosition - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        specular = spec * vec3(texture(material.specular, TexCoords)) * light.specular;

        if(theta < light.cutOff) {
            diffuse *= intensity;
            specular *= intensity;
        }
    }

    // FragColor =  vec4(ambient + diffuse + specular, 1.0);
    FragColor =  vec4(ambient + diffuse + specular, 1.0);

}