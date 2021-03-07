#pragma once

#include <glad/glad.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Projection
{
private:
	glm::mat4 projection;

	GLfloat fovy;
	GLfloat aspect;
	GLfloat zNear;
	GLfloat zFar;
public:
	Projection(float _aspect, float _fovy = glm::radians(45.0f), float _zNear = 0.1f, float _zFar = 100.0f);
	glm::mat4 getProjection();
	void setProgection(float _aspect);
	void setProjection(float _aspect, float _fovy);
	void setProjection(float _aspect, float _fovy, float _zNear, float _zFar);
};