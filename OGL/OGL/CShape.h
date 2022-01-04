#pragma once
#include "NumptyBehavior.h"
#include "CShaderLoader.h"

class CShape :	public NumptyBehavior
{
public:
    virtual void Start() = 0;
    virtual void Input(GLFWwindow* window, int key, int scancode, int action, int mods) {};
    virtual void Update(float _dt) {};
    virtual void Render() = 0;

protected:
    GLuint VAO, VBO, EBO;
    GLuint m_ShaderProgram;

    GLfloat x = 0.0f;
    GLfloat y = 0.0f;
    GLfloat z = 0.0f;

    GLfloat aspectRatio = 1.77777777778; // 16:9
};

