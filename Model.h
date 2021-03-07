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
    // ������ ������ 
    vector<Texture> textures_loaded; // (�����������) ��������� ��� ����������� ��������, ����� ���������, ��� ��� �� ��������� ����� ������ ����
    vector<Mesh> meshes;
    string directory;
    bool gammaCorrection;

    // ����������� � �������� ��������� ���������� ���� � 3D-������
    Model(string const& path, bool gamma = false);

    // ������������ ������, � ������ � ��� � ����
    void Draw(Shader shader);

private:
    // ��������� ������ � ������� Assimp � ��������� ���������� ���� � ������� meshes
    void loadModel(string const& path);

    // ����������� ��������� ����. ������������ ������ ��������� ���, ������������� � ����, � ��������� ���� ������� ��� ����� �������� ����� (���� ������ ������ �������)
    void processNode(aiNode* node, const aiScene* scene);

    Mesh processMesh(aiMesh* mesh, const aiScene* scene);

    // ��������� ��� �������� ���������� ��������� ���� � �������� ��������, ���� ��� ��� �� ���� ���������.
    // ����������� ���������� ������������ � ���� ��������� Texture
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};
