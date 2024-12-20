#pragma once
#include <glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace CamConsts {
    enum class CameraMovement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    const float YAW = -90.0f;
    const float PITCH = 0.0f;
    const float SPEED = 7.0f;
    const float SENSITIVITY = 0.15f;
    const float ZOOM = 45.0f;
}


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = CamConsts::YAW, float pitch = CamConsts::PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(CamConsts::SPEED), MouseSensitivity(CamConsts::SENSITIVITY), Zoom(CamConsts::ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
        m_Projection = glm::perspective(glm::radians(80.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    }
    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(CamConsts::SPEED), MouseSensitivity(CamConsts::SENSITIVITY), Zoom(CamConsts::ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix();

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(CamConsts::CameraMovement direction, float deltaTime);

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

public:
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    glm::mat4 m_Projection;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();
};