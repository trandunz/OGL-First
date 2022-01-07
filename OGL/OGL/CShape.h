#pragma once
#include "NumptyBehavior.h"
#include "Shader.h"
#include "CCamera.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

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
    GLuint VAO, VBO, EBO;
    Shader* m_Shader;

    Vector3 m_Velocity;

    GLfloat aspectRatio = 1.77777777778; // 16:9
};

