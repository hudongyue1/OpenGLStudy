//
// Created by 胡栋月 on 10/1/23.
//

#ifndef OPENGLSTUDY_CAMERA_H
#define OPENGLSTUDY_CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

enum Camera_Movement {
    FORWARD,
    BACKEND,
    LEFT,
    RIGHT
};

// Default camera values
const float DEFAULT_YAW = -90.0f;
const float DEFAULT_PITCH = 0.0f;
const float DEFAULT_SPEED = 2.5f;
const float DEFAULT_ROTATE_SENSITIVITY = 0.1f;
const float DEFAULT_SCROLL_SENSITIVITY = 0.5f;
const float DEFAULT_FOV = 45.0f;

class Camera {
public:
    // attribute
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 WorldUp;
    glm::vec3 Right;
    // Euler angle
    float Yaw;
    float Pitch;
    float Roll;
    // options
    float MoveSpeed;
    float RotateSensitivity;
    float Fov;

    // default constructor
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = DEFAULT_YAW, float pitch = DEFAULT_PITCH) :
           Front(glm::vec3(0.0f, 0.0f, -1.0f)), MoveSpeed(DEFAULT_SPEED),
           RotateSensitivity(DEFAULT_ROTATE_SENSITIVITY), Fov(DEFAULT_FOV) {
        Position = position;
        WorldUp = worldUp;
        Yaw = yaw;
        Pitch = pitch;
        UpdateCameraMatrix();
    }

    glm::mat4 GetViewMatrix() {
        return glm::lookAt(Position, Position + Front, WorldUp);
    }

    // handle keyboard input
    void ProcessKeyBoard(const Camera_Movement direction, const float deltaTime) {
        float velocity = MoveSpeed * deltaTime;
        if(direction == FORWARD) Position += Front * velocity;
        if(direction == BACKEND) Position -= Front * velocity;
        if(direction == RIGHT) Position += Right * velocity;
        if(direction == LEFT) Position -= Right * velocity;
    }

    // handle mouse input
    void ProcessMouse(float xOffset, float yOffset) {
        xOffset *= RotateSensitivity;
        yOffset *= RotateSensitivity;

        Yaw += xOffset;
        Pitch += yOffset;

        if(Pitch > 89.0f) Pitch = 89.0f;
        if(Pitch < -89.0f) Pitch = -89.0;
        UpdateCameraMatrix();
    }

    // handle scroll
    void ProcessScroll(float yOffset) {
        Fov -= (float) yOffset * DEFAULT_SCROLL_SENSITIVITY;
        if(Fov < 1.0f) Fov = 1.0f;
        if(Fov > 45.0f) Fov = 45.0f;
    }

private:
    // update view/camera matrix
    void UpdateCameraMatrix() {
        glm::vec3 cameraFront;
        cameraFront.x = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
        cameraFront.y = sin(glm::radians(Pitch));
        cameraFront.z = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));
        Front = glm::normalize(cameraFront);
        Right = glm::normalize(glm::cross(cameraFront, WorldUp));
        Up = glm::normalize(glm::cross(Right, Front));
    }
};

#endif //OPENGLSTUDY_CAMERA_H
