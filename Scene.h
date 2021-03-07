#pragma once

#include <glad/glad.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"    

#include "Shader.h"
//#include "stb_image.h"
#include "model.h"

#include "DirLight.h"
#include "Floor.h"

class Scene
{
protected:
	Shader ourShader;

	// Загрузка моделей
	//Model ourModel;
	DirLight light;

	Floor floor;
	Floor wall1;
	Floor wall2;
	Floor wall3;
	Floor wall4;
	Floor roof;

	Model armchair1;
	Model armchair2;
	Model sofa;
	Model table;
	Model bureau;
	Model statue;
	Model guitar;
	//Model chandelier;

public:
	Scene();
	~Scene();
	void drawScene(glm::mat4 projection, glm::mat4 viev, glm::vec3 cameraPos, float _xpos, float _zpos, float _rotate);
};

