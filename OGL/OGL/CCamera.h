#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "NumptyBehavior.h"

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default Values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera : NumptyBehavior
{
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;
    float Pitch;
 
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    Camera(std::map<int, bool>& _keyMap, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : 
        Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        m_KeyPresses = &_keyMap;
        UpdateCameraVectors();
    }
    Camera(std::map<int, bool>& _keyMap, float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : 
        Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        m_KeyPresses = &_keyMap;
        UpdateCameraVectors();
    }
    ~Camera() { m_KeyPresses = nullptr; }

    inline glm::mat4 GetViewMatrix() { return glm::lookAt(Position, Position + Front, Up); }

    void Movement(long double _dt)
    {
        UpdatePosition(m_InputVec.x * MovementSpeed * _dt, m_InputVec.y * MovementSpeed * _dt, m_InputVec.z * MovementSpeed * _dt);
    }
    bool UpdatePosition(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f)
    {
        bool moved = false;
        if (_x >= 0.000000001 || _x <= -0.000000001)
        {
            Position += Right * _x;
            moved = true;
        }
        if (_y >= 0.000000001 || _y <= -0.000000001)
        {
            Position += Front * _y;
            moved = true;
        }
        if (_z >= 0.000000001 || _z <= -0.000000001)
        {
            Position += Front * _z;
            moved = true;
        }

        return moved;
    }

    void Input(float deltaTime)
    {
        // Reset Input Vec
        m_InputVec.x = 0.0f;
        m_InputVec.y = 0.0f;
        m_InputVec.z = 0.0f;

        // Resett Move Speed For Sprint
        MovementSpeed = 1.0f;

        for (auto& item : (*m_KeyPresses))
        {
            if (item.second == true)
            {
                switch (item.first)
                {
                case GLFW_KEY_D:
                {
                    m_InputVec.x = 1;
                    break;
                }
                case GLFW_KEY_A:
                {
                    m_InputVec.x = -1;
                    break;
                }
                case GLFW_KEY_W:
                {
                    m_InputVec.y = 1;
                    break;
                }
                case GLFW_KEY_S:
                {
                    m_InputVec.y = -1;
                    break;
                }
                case GLFW_KEY_LEFT_SHIFT:
                {
                    MovementSpeed = 5.0f;
                    break;
                }
                default:
                    break;
                }
            }
        }

        glm::normalize(m_InputVec);
    }
    void ProcessMouse(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        projectionMatrix = glm::perspective(glm::radians(Zoom), 1920.0f / 1080.0f, 0.1f, 100.0f);

        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        UpdateCameraVectors();
    }
    void ProcessScroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }

    glm::mat4 projectionMatrix = glm::perspective(glm::radians(Zoom), 1920.0f / 1080.0f, 0.1f, 100.0f);
private:
    void UpdateCameraVectors()
    {
        glm::vec3 newFront;
        newFront.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        newFront.y = sin(glm::radians(Pitch));
        newFront.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(newFront);
        // also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = glm::normalize(glm::cross(Right, Front));
    }

    std::map<int, bool>* m_KeyPresses = nullptr;
    glm::vec3 m_InputVec;
};
#endif

