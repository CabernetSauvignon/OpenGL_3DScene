#include <glad/glad.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// ��������� ������ �� ���������
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 6.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
private:
    // �������� ������
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // ���� ������
    float Yaw;
    float Pitch;
    // ��������� ������
    float MovementSpeed;
    float MouseSensitivity;

public:
    Camera(glm::vec3 position = glm::vec3(-10.0f, 5.25f, 10.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
    glm::mat4 GetViewMatrix();
    glm::vec3 GetPosition();
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

private:
    void updateCameraVectors();
};