#pragma once
#include "NumptyBehavior.h"
#include "CCamera.h"

namespace Harmony
{
    class MousePicker : public NumptyBehavior
    {
    public:
        MousePicker(Camera* _camera)
        {
            m_Camera = _camera;
            m_ViewMatrix = m_Camera->GetViewMatrix();
            m_ProjectionMatrix = m_Camera->GetProjectionMatrix();
        }
        ~MousePicker()
        {
            m_Camera = nullptr;
        }

        void GrabMousePosition(double _xPos, double _yPos)
        {
            m_MouseX = _xPos;
            m_MouseY = _yPos;
        }

        void Update()
        {
            m_ViewMatrix = m_Camera->GetViewMatrix();
            m_ProjectionMatrix = m_Camera->GetProjectionMatrix();
            m_CurrentRay = CalculateMouseRay(m_MouseX, m_MouseY);
        }

        glm::vec3 GetCurrentRay()
        {
            return m_CurrentRay;
        }

        float Range = 10.0f;
    private:

        //glm::vec3 m_CurrentTerrainPoint;
        glm::vec3 m_CurrentRay{ 0,0,0 };
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        Camera* m_Camera = nullptr;

        double m_MouseX = 0.0;
        double m_MouseY = 0.0;

        glm::vec3 CalculateMouseRay(double _xPos, double _yPos)
        {
            glm::vec2 mousePos = GetNormalizedDeviceCoords((float)_xPos, (float)_yPos);
            glm::vec4 clipCoords = glm::vec4(mousePos.x, mousePos.y, -1, 1);
            glm::vec4 eyeCoords = ToEyeCoords(clipCoords);
            glm::vec3 wordRay = ToWorldCoords(eyeCoords);
            return wordRay;
        }

        glm::vec3 ToWorldCoords(glm::vec4 _clipCoords)
        {
            glm::mat4 invertView = glm::inverse(m_ViewMatrix);
            glm::vec4 rayWorld = _clipCoords * m_ViewMatrix;
            glm::vec3 mouseRay{ rayWorld.x,rayWorld.y,rayWorld.z };
            mouseRay = glm::normalize(mouseRay);
            return glm::vec3(mouseRay.x, mouseRay.y, mouseRay.z);
        }

        glm::vec4 ToEyeCoords(glm::vec4 _clipCoords)
        {
            glm::mat4 invertProj = glm::inverse(m_ProjectionMatrix);
            glm::vec4 eyeCoords = _clipCoords * invertProj;
            return glm::vec4(eyeCoords.x, eyeCoords.y, -1, 0);
        }

        glm::vec2 GetNormalizedDeviceCoords(double _xPos, double _yPos)
        {
            double x = ((2.0f * _xPos) / 1920) - 1;
            double y = ((2.0f * _yPos) / 1080) - 1;
            return glm::vec2(x, y);
        }

        glm::vec3 GetPointOnRay(glm::vec3 _ray, float _distance)
        {
            glm::vec3 camPos = m_Camera->Position;
            glm::vec3 start = glm::vec3(camPos.x, camPos.y, camPos.z);
            glm::vec3 scaledRay = glm::vec3(_ray.x * _distance, _ray.y * _distance, _ray.z * _distance);
            return scaledRay + start;
        }
    };
}

