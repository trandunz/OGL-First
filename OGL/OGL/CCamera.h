#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "Includes.h"
#include "GUI.h"

namespace Harmony
{
    enum Camera_Movement
    {
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

    class Camera
    {
    public:
        Camera(std::map<int, bool>& _keyMap, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
        Camera(std::map<int, bool>& _keyMap, float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
        ~Camera();

        inline glm::mat4 GetViewMatrix() 
        {
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), Position);
            return m_Perspective ? glm::lookAt(Position, Position + Front, Up) : glm::inverse(transform);
        }
        inline glm::mat4 GetProjectionMatrix()
        {
            if (m_Perspective)
                return glm::perspective(glm::radians(Zoom), 1920.0f / 1080.0f, 0.1f, 100.0f);
            else
                return glm::ortho(-(100 * 0.5f * (1 / Zoom)), 100 * 0.5f * (1 / Zoom), -(100 * 0.5f * (1 / Zoom)), 100 * 0.5f * (1 / Zoom), 0.1f, 100.0f);
        }

        void Input();
        void Movement(long double _dt);
        void ProcessMouse(float xoffset, float yoffset, GLboolean constrainPitch = true);
        void ProcessScroll(float yoffset);

        bool UpdatePosition(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f);
        bool SetPerspective();

        void ImGUIHandler();
        void ImGUIHandler(const char* _type);

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

        bool m_CamLightEnabled = false;

    private:
        void UpdateCameraVectors();

       
        bool m_Perspective = true;
        std::map<int, bool>* m_KeyPresses = nullptr;

        glm::vec3 m_InputVec;
    };
}

#endif

