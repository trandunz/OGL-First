#pragma once
#include "NumptyBehavior.h"
class CCircle : public NumptyBehavior
{
public:
    void Start();
    void Input(GLFWwindow* window, int key, int scancode, int action, int mods);
    void Update();
    void Render();

private:
    // cIRCLE
    float radius = 0.25f;
    float r = 0.0f;
    float g = 0.3f;
    float b = 0.6f;

    // 0 is middle, 1 is the whole screen
    float x = 0;
    float y = 1;
};

