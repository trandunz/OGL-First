#pragma once
#include "CShape.h"

class CTriangle : public CShape
{
public:
    virtual ~CTriangle();
    void Start();
    void Input(GLFWwindow* window, int key, int scancode, int action, int mods);
    void Update();
    void Render();
private:
    GLfloat vertices[9]
    {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
    };
};

