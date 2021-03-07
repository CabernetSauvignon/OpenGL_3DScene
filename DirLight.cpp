#include "DirLight.h"

/*glm::vec3 position;

glm::vec4 ambient;
glm::vec4 diffuse;
glm::vec4 specular;

float constant;
float linear;
float quadratic;*/

DirLight::DirLight(glm::vec3 _position)
{
	position = _position;

	ambient = glm::vec4(0.05f, 0.05f, 0.05f, 0.05f);
	diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	constant = 1.0f;
	linear = 0.014f;
	quadratic = 0.00107f;
}

void DirLight::setLight(Shader shader)
{
	//shader.Set_Float4v_Uniform("material.specular", 1, glm::value_ptr(specular));
	//ourShader.Set_Matrix4fv_Uniform("model", 1, GL_FALSE, &modelc[0][0]);
	shader.Set_Float4v_Uniform("light.ambient", 1, &ambient[0]);
	shader.Set_Float4v_Uniform("light.diffuse", 1, &diffuse[0]);
	shader.Set_Float4v_Uniform("light.specular", 1, &specular[0]);
	shader.Set_Float1_Uniform("light.constant", constant);
	shader.Set_Float1_Uniform("light.linear", linear);
	shader.Set_Float1_Uniform("light.quadratic", quadratic);
	shader.Set_Float3v_Uniform("light.position", 1, &position[0]);
}
