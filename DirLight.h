#pragma once

#include <glad/glad.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp" 
#include "Shader.h"

class DirLight
{
private:
    glm::vec3 position;

    glm::vec4 ambient;
    glm::vec4 diffuse;
    glm::vec4 specular;

    float constant;
    float linear;
    float quadratic;

public:
    DirLight(glm::vec3 _position  = glm::vec3(0.0f, 0.0f, 0.0f));
    void setLight(Shader shader);
};

