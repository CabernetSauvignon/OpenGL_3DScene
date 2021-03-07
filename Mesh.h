#pragma once

#include <glad/glad.h> // содержит все объявления OpenGL-типов

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Shader.h" // shader.h идентичен файлу shader_s.h

#include <string>
#include <vector>
using namespace std;

struct Vertex {

    // Позиция
    glm::vec3 Position;

    // Нормаль
    glm::vec3 Normal;

    // Текстурные координаты
    glm::vec2 TexCoords;

    // Касательный вектор
    glm::vec3 Tangent;

    // Вектор бинормали (вектор, перпендикулярный касательному вектору и вектору нормали)
    glm::vec3 Bitangent;
};

struct Texture {
    unsigned int id;
    string type;
    string path;
};

class Mesh {
public:
    // Данные меша
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    unsigned int VAO;

    // Конструктор
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

    // Рендеринг меша
    void Draw(Shader& shader);

private:
    // Данные для рендеринга 
    unsigned int VBO, EBO;

    // Инициализируем все буферные объекты/массивы
    void setupMesh();
};
