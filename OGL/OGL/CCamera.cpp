#include "CCamera.h"

namespace Harmony
{
    Camera::Camera(std::map<int, bool>& _keyMap, float _posX, float _posY, float _posZ, float _upX, float _upY, float _upZ, float _yaw, float _pitch)
        :
        Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED),
        MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = glm::vec3(_posX, _posY, _posZ);
        WorldUp = glm::vec3(_upX, _upY, _upZ);
        Yaw = _yaw;
        Pitch = _pitch;
        m_KeyPresses = &_keyMap;
        UpdateCameraVectors();
    }

    Camera::Camera(std::map<int, bool>& _keyMap, glm::vec3 _position, glm::vec3 _up, float _yaw, float _pitch)
        :
        Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED),
        MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = _position;
        WorldUp = _up;
        Yaw = _yaw;
        Pitch = _pitch;
        m_KeyPresses = &_keyMap;
        UpdateCameraVectors();
    }

    Camera::~Camera()
    {
        m_KeyPresses = nullptr;
    }

    void Camera::Movement(long double _dt)
    {
        if (m_Perspective)
            UpdatePosition(m_InputVec.x * MovementSpeed * _dt, m_InputVec.y * MovementSpeed * _dt, m_InputVec.z * MovementSpeed * _dt);
    }

    bool Camera::UpdatePosition(float _x, float _y, float _z)
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

    bool Camera::SetPerspective()
    {
        m_Perspective = !m_Perspective;
        return m_Perspective;
    }

    void Camera::ImGUIHandler()
    {
        if (ImGui::CollapsingHeader("Camera Settings"))
        {
            ImGui::Text("");
            ImGui::Text("MovementSpeed");
            {
                ImGui::SliderFloat(":Camera Movespeed", &MovementSpeed, 0, 500);
            }
        }
    }

    void Camera::ImGUIHandler(const char* _type)
    {
        if (_type == "DebugInfo")
        {
            ImGUIHandler();
        }
        else if (_type == "MenuBar")
        {
            if (ImGui::BeginMenu("Camera"))
            {
                if (ImGui::MenuItem("Toggle Perspective", "Yes")) 
                { 
                    SetPerspective();
                }
                ImGui::EndMenu();
            }
        }
    }

    void Camera::Input()
    {
        // Reset Input Vec
        m_InputVec.x = 0.0f;
        m_InputVec.y = 0.0f;
        m_InputVec.z = 0.0f;

        // Resett Move Speed For Sprint
       // MovementSpeed = 1.0f;

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
                    // MovementSpeed = 5.0f;
                    break;
                }
                default:
                    break;
                }
            }
        }

        glm::normalize(m_InputVec);
    }

    void Camera::ProcessMouse(float xoffset, float yoffset, GLboolean constrainPitch)
    {
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

    void Camera::ProcessScroll(float yoffset)
    {
        Zoom -= (float)yoffset;

        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f && m_Perspective)
            Zoom = 45.0f;
    }

    void Camera::UpdateCameraVectors()
    {
        glm::vec3 newFront;
        newFront.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        newFront.y = sin(glm::radians(Pitch));
        newFront.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(newFront);
        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up = glm::normalize(glm::cross(Right, Front));
    }

}
