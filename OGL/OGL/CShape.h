#pragma once
#include "NumptyBehavior.h"
#include "CShaderLoader.h"
#include "CCamera.h"

class CShape :	public NumptyBehavior
{
public:
    virtual void Start() = 0;
    virtual void Input(GLFWwindow* window, int key, int scancode, int action, int mods) {};
    virtual void Update(float _dt) {};
    virtual void Render() {};

protected:
    GLuint VAO, VBO, EBO;
    GLuint m_ShaderProgram;

    Vector3 m_Velocity;

    GLfloat aspectRatio = 1.77777777778; // 16:9
};

