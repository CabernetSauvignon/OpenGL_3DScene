#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "stb_image.h"
#include "Shader.h"

class Floor
{
private:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	unsigned int diff_texture;
	unsigned int spec_texture;
public:
	Floor(const char* diff_tex, const char* spec_tex, GLfloat length = 100.0f, GLfloat width = 100.0f);
	~Floor();
	void Draw(Shader& shader);
};

