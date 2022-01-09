#ifndef CAMERA_H
#define CAMERA_H

#include "NumptyBehavior.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera : NumptyBehavior
{
public:
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // constructor with vectors
    Camera(std::map<int, bool>& _keyMap, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        m_KeyPresses = &_keyMap;
        updateCameraVectors();
    }
    // constructor with scalar values
    Camera(std::map<int, bool>& _keyMap, float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        m_KeyPresses = &_keyMap;
        updateCameraVectors();
    }

    ~Camera() { m_KeyPresses = nullptr; }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(float deltaTime)
    {
        m_InputVec.x = 0.0f;
        m_InputVec.y = 0.0f;
        m_InputVec.z = 0.0f;
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

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = glm::normalize(glm::cross(Right, Front));
    }

    std::map<int, bool>* m_KeyPresses = nullptr;

    glm::vec3 m_InputVec;
};
#endif

