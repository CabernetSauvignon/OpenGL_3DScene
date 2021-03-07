#pragma once

#include <glad/glad.h> 

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"
#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);

class Model
{
public:
    // ƒанные модели 
    vector<Texture> textures_loaded; // (оптимизаци€) сохран€ем все загруженные текстуры, чтобы убедитьс€, что они не загружены более одного раза
    vector<Mesh> meshes;
    string directory;
    bool gammaCorrection;

    //  онструктор в качестве аргумента использует путь к 3D-модели
    Model(string const& path, bool gamma = false);

    // ќтрисовываем модель, а значит и все еЄ меши
    void Draw(Shader shader);

private:
    // «агружаем модель с помощью Assimp и сохран€ем полученные меши в векторе meshes
    void loadModel(string const& path);

    // –екурсивна€ обработка узла. ќбрабатываем каждый отдельный меш, расположенный в узле, и повтор€ем этот процесс дл€ своих дочерних углов (если таковы вообще имеютс€)
    void processNode(aiNode* node, const aiScene* scene);

    Mesh processMesh(aiMesh* mesh, const aiScene* scene);

    // ѕровер€ем все текстуры материалов заданного типа и загружам текстуры, если они еще не были загружены.
    // Ќеобходима€ информаци€ возвращаетс€ в виде структуры Texture
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};
