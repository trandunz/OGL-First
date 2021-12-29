#pragma once
#include "NumptyBehavior.h"
#include "CShaderLoader.h"

class CShape :	public NumptyBehavior
{
public:
    virtual void Start() = 0;
    virtual void Input(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;

protected:
    GLuint VAO, VBO, EBO;
    GLuint m_ShaderProgram;

    GLfloat x = 0.0f;
    GLfloat y = 0.0f;
};

