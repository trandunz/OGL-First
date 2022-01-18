#pragma once
#include "NumptyBehavior.h"
#include "CCamera.h"
class MousePicker : public NumptyBehavior
{
public:
    MousePicker(Camera* _camera, glm::mat4& _projMat)
    {
        m_Camera = _camera;
        m_ProjectionMatrix = _projMat;
        m_ViewMatrix = m_Camera->GetViewMatrix();
    }

    void GrabMousePosition(double _xPos, double _yPos)
    {
        m_MouseX = _xPos;
        m_MouseY = _yPos;
    }

    void Update()
    {
        m_ViewMatrix = m_Camera->GetViewMatrix();
        m_CurrentRay = CalculateMouseRay(m_MouseX, m_MouseY);

        if (IntersectionInRange(0, 100, m_CurrentRay)) 
        {
            m_CurrentTerrainPoint = BinarySearch(0, 0, 100, m_CurrentRay);
        }
        else 
        {
            m_CurrentTerrainPoint = glm::vec3(0);
        }
    }

    void ProcessMovement(glm::vec3 _movePerFrame)
    {
        Transform.position = _movePerFrame;
    }

    glm::vec3 GetCurrentRay()
    {
        return m_CurrentRay;
    }

    glm::vec3 GetCurrentTerrainPoint() 
    {
        return m_CurrentTerrainPoint;
    }

    float Range = 10.0f;
    STransform Transform;
private:

    glm::vec3 m_CurrentTerrainPoint;
    glm::vec3 m_CurrentRay;
    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewMatrix;
    Camera* m_Camera = nullptr;
    
    double m_MouseX = 0.0;
    double m_MouseY = 0.0;

    glm::vec3 CalculateMouseRay(double _xPos, double _yPos)
    {
        glm::vec2 mousePos = GetNormalizedDeviceCoords(_xPos, _yPos);
        glm::vec4 clipCoords = glm::vec4(mousePos.x, mousePos.y, -1, 1);
        glm::vec4 eyeCoords = ToEyeCoords(clipCoords);
        glm::vec3 wordRay = ToWorldCoords(eyeCoords);
        return wordRay;
    }

    glm::vec3 ToWorldCoords(glm::vec4 _clipCoords)
    {
        glm::mat4 invertView = glm::inverse(m_ViewMatrix);
        glm::vec4 rayWorld = _clipCoords * m_ViewMatrix;
        glm::vec3 mouseRay{ rayWorld .x,rayWorld .y,rayWorld .z};
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
    glm::vec3 BinarySearch(int _count, float _start, float _finish, glm::vec3 _ray) 
    {
        float half = _start + ((_finish - _start) / 2.f);
        if (_count >= 10)
        {
            glm::vec3 endPoint = GetPointOnRay(_ray, half);
            // Check Intersection
            if (true)
            {
                return endPoint;
            }
            else if (false)
            {
                return glm::vec3(0);
            }
        }
        if (IntersectionInRange(_start, half, _ray))
        {
            return BinarySearch(_count + 1, _start, half, _ray);
        }
        else 
        {
            return BinarySearch(_count + 1, half, _finish, _ray);
        }
    }
    bool IntersectionInRange(float _start, float _finish, glm::vec3 _ray) 
    {
        glm::vec3 startPoint = GetPointOnRay(_ray, _start);
        glm::vec3 endPoint = GetPointOnRay(_ray, _finish);
        if (!IsUnderGround(startPoint) && IsUnderGround(endPoint)) 
        {
            return true;
        }
        else 
        {
            return false;
        }
    }
    bool IsUnderGround(glm::vec3 _testPoint) 
    {
        float height = 0;
        /*Terrain terrain = getTerrain(_testPoint.getX(), _testPoint.getZ());*/
        /*if (terrain != null) 
        {
            height = terrain.getHeightOfTerrain(_testPoint.Transform.Position.x, _testPoint.Transform.Position.z);
        }*/
        if (_testPoint.y < height) 
            return true;
        else
            return false;
    }
};

