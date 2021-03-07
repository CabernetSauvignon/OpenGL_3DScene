#version 330 core

struct PointLight
{
    vec3 position;

    vec4 ambient;
    vec4 diffuse;
    vec4 specular;

    float constant;
    float linear;
    float quadratic;
};

vec4 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular2;
uniform float shininess;
uniform PointLight light;
uniform vec3 viewPos;

in vec3 fragPos;
in vec3 normal;
in vec2 tex;

out vec4 outputColor;

void main()
{   
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(viewPos - fragPos);
    
    outputColor += CalcPointLight(light, normal, fragPos, viewDir);
    //outputColor = texture(texture_diffuse1, tex);
}

vec4 CalcPointLight(PointLight light, vec3 norm, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position- fragPos);

    // Рассеяное затенение
    float diff = max(dot(norm, lightDir), 0.0);

    // Составляющая отражения
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    // Затухание света
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // Комбинируем результаты
    vec4 ambient = light.ambient * vec4(texture(texture_diffuse1, tex).rgb, 1.0);
    vec4 diffuse = light.diffuse * (diff * vec4(texture(texture_diffuse1, tex).rgb, 1.0));
    vec4 specular = light.specular * spec * vec4(texture(texture_specular2, tex).rgb, 1.0);
    //vec4 specular = light.specular * (spec * material.specular);
    ambient *= attenuation ;
    diffuse *= attenuation ;
    specular *= attenuation ;
    return (ambient + diffuse + specular);
}

/*

vec4 CalcPointLight(PointLight light, vec3 norm, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position- fragPos);

    // Рассеяное затенение
    float diff = max(dot(norm, lightDir), 0.0);

    // Составляющая отражения
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // Затухание света
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // Комбинируем результаты
    vec4 ambient = light.ambient * vec4(texture(material.diffuse, tex).rgb, 1.0);
    vec4 diffuse = light.diffuse * (diff * vec4(texture(material.diffuse, tex).rgb, 1.0));
    vec4 specular = light.specular * (spec * material.specular);
    ambient *= attenuation ;
    diffuse *= attenuation ;
    specular *= attenuation ;
    return (ambient + diffuse + specular);
}*/