#version 330 core
layout (location = 0) in vec3 figurePos;
layout (location = 1) in vec3 figureNormal;
layout (location = 2) in vec2 textureCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 tex;
out vec3 fragPos;
out vec3 normal;

void main()
{
    //normal = mat3(transpose(inverse(model))) * figureNormal;
    normal = figureNormal;
    fragPos = vec3(model * vec4(figurePos, 1.0));
    tex = textureCoords;    
    gl_Position = projection * view * model * vec4(figurePos, 1.0);
}