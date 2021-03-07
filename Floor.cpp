#include "Floor.h"

/*
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	unsigned int diff_texture;
	unsigned int spec_texture;
public:*/
Floor::Floor(const char* diff_tex, const char* spec_tex, GLfloat length, GLfloat width)
{
	GLfloat half_length = length / 2.0f;
	GLfloat half_width = width / 2.0f;

	GLfloat vertices[] =
	{
		// Координаты                      //Нормаль            //Текстурные координаты
		-half_width, 0.0f, -half_length,   0.0f, 1.0f, 0.0f,     0.0f, 0.0f,
		+half_width, 0.0f, -half_length,   0.0f, 1.0f, 0.0f,     width / 10, 0.0f,
		+half_width, 0.0f, +half_length,   0.0f, 1.0f, 0.0f,     width / 10, length / 10,
		-half_width, 0.0f, +half_length,   0.0f, 1.0f, 0.0f,     0.0f, length / 10
	};

	GLuint indices[] = { 0, 1, 2, 2, 3, 0 };

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glGenTextures(1, &diff_texture);
	glGenTextures(1, &spec_texture);
	glBindTexture(GL_TEXTURE_2D, diff_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int _width, _height, nrChannels;
	unsigned char* data = stbi_load(diff_tex, &_width, &_height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, spec_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	data = stbi_load(spec_tex, &_width, &_height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Floor::~Floor()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Floor::Draw(Shader& shader)
{
	glActiveTexture(GL_TEXTURE0);
	shader.Set_Int1_Uniform("texture_diffuse1", 0);
	glBindTexture(GL_TEXTURE_2D, diff_texture);

	glActiveTexture(GL_TEXTURE1);
	shader.Set_Int1_Uniform("texture_specular2", 1);
	glBindTexture(GL_TEXTURE_2D, spec_texture);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glEnable(GL_CULL_FACE);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}
