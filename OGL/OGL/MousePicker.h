#pragma once
#include "NumptyBehavior.h"
#include "CCamera.h"
class MousePicker :
    public NumptyBehavior
{
public:
    MousePicker(Camera* _camera, glm::mat4& _projMat)
    {
        m_Camera = _camera;
        m_ProjectionMatrix = _projMat;
        m_ViewMatrix = m_Camera->GetViewMatrix();
    }

    void GrabMousePosition(double xPos, double yPos)
    {
        m_MouseX = xPos;
        m_MouseY = yPos;
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
        transform.position = _movePerFrame;
    }

    glm::vec3 GetCurrentRay()
    {
        return m_CurrentRay;
    }

    glm::vec3 GetCurrentTerrainPoint() {
        return m_CurrentTerrainPoint;
    }

    float range = 10.0f;
    Transform transform;
private:

    glm::vec3 m_CurrentTerrainPoint;
    glm::vec3 m_CurrentRay;
    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewMatrix;
    Camera* m_Camera = nullptr;
    
    double m_MouseX = 0.0;
    double m_MouseY = 0.0;

    glm::vec3 CalculateMouseRay(double xPos, double yPos)
    {
        glm::vec2 mousePos = GetNormalizedDeviceCoords(xPos, yPos);
        glm::vec4 clipCoords = glm::vec4(mousePos.x, mousePos.y, -1, 1);
        glm::vec4 eyeCoords = ToEyeCoords(clipCoords);
        glm::vec3 wordRay = ToWorldCoords(eyeCoords);
        return wordRay;
    }

    glm::vec3 ToWorldCoords(glm::vec4 clipCoords)
    {
        glm::mat4 invertView = glm::inverse(m_ViewMatrix);
        glm::vec4 rayWorld = clipCoords * m_ViewMatrix;
        glm::vec3 mouseRay{ rayWorld .x,rayWorld .y,rayWorld .z};
        mouseRay = glm::normalize(mouseRay);
        return glm::vec3(mouseRay.x, mouseRay.y, mouseRay.z);
    }

    glm::vec4 ToEyeCoords(glm::vec4 clipCoords)
    {
        glm::mat4 invertProj = glm::inverse(m_ProjectionMatrix);
        glm::vec4 eyeCoords = clipCoords * invertProj;
        return glm::vec4(eyeCoords.x, eyeCoords.y, -1, 0);
    }

    glm::vec2 GetNormalizedDeviceCoords(double xPos, double yPos)
    {
        double x = ((2.0f * xPos) / 1920) - 1;
        double y = ((2.0f * yPos) / 1080) - 1;
        return glm::vec2(x, y);
    }

    glm::vec3 GetPointOnRay(glm::vec3 ray, float distance) 
    {
        glm::vec3 camPos = m_Camera->Position;
        glm::vec3 start = glm::vec3(camPos.x, camPos.y, camPos.z);
        glm::vec3 scaledRay = glm::vec3(ray.x * distance, ray.y * distance, ray.z * distance);
        return scaledRay + start;
    }
    glm::vec3 BinarySearch(int count, float start, float finish, glm::vec3 ray) {
        float half = start + ((finish - start) / 2.f);
        if (count >= 10) 
        {
            glm::vec3 endPoint = GetPointOnRay(ray, half);
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
        if (IntersectionInRange(start, half, ray)) 
        {
            return BinarySearch(count + 1, start, half, ray);
        }
        else 
        {
            return BinarySearch(count + 1, half, finish, ray);
        }
    }
    bool IntersectionInRange(float start, float finish, glm::vec3 ray) 
    {
        glm::vec3 startPoint = GetPointOnRay(ray, start);
        glm::vec3 endPoint = GetPointOnRay(ray, finish);
        if (!IsUnderGround(startPoint) && IsUnderGround(endPoint)) 
        {
            return true;
        }
        else 
        {
            return false;
        }
    }
    bool IsUnderGround(glm::vec3 testPoint) 
    {
        /*Terrain terrain = getTerrain(testPoint.getX(), testPoint.getZ());*/
        float height = 0;
        /*if (terrain != null) {
            height = terrain.getHeightOfTerrain(testPoint.getX(), testPoint.getZ());
        }*/
        if (testPoint.y < height) {
            return true;
        }
        else {
            return false;
        }
    }
};

