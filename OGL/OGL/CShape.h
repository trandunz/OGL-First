#pragma once
#include "NumptyBehavior.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

class CShape :	public NumptyBehavior
{
public:
    virtual ~CShape()
    {
        CleanupPointer(m_Shader);
    }

    virtual void Start() = 0;
    virtual void Input(GLFWwindow* window, int key, int scancode, int action, int mods) {};
    virtual void Update(float _dt) {};
    virtual void Render() {};
protected:
    Shader* m_Shader;
    Renderer m_Renderer;

    float m_Scale = 5.0f;

    Vector3 m_Velocity;
};

