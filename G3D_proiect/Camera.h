#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <math.h> 
#include <GL/glew.h>

#define GLM_FORCE_CTOR_INIT 

#include <glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

enum ECameraMovementType
{
    UNKNOWN,
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera
{
private:
    // Default camera values
    const float zNEAR = 0.1f;
    const float zFAR = 500.f;
    const float YAW = -90.0f;
    const float PITCH = 0.0f;
    const float FOV = 45.0f;
    glm::vec3 startPosition;
    void UpdateCameraVectors();


public: 
    Camera(const int width, const int height, const glm::vec3& position);
    void Set(const int width, const int height, const glm::vec3& position);
    const glm::vec3 GetPosition() const;
    const glm::mat4 GetViewMatrix() const;
    const glm::mat4 GetProjectionMatrix() const;
    void ProcessKeyboard(ECameraMovementType direction, float deltaTime);

protected:
    const float cameraSpeedFactor = 2.5f;
    const float mouseSensitivity = 0.1f;

    // Perspective properties
    float zNear;
    float zFar;
    float FoVy;
    int width;
    int height;
    bool isPerspective;

    glm::vec3 position;
    glm::vec3 forward;
    glm::vec3 right;
    glm::vec3 up;
    glm::vec3 worldUp;

    // Euler Angles
    float yaw;
    float pitch;

    bool bFirstMouseMove = true;
    float lastX = 0.f, lastY = 0.f;

};

