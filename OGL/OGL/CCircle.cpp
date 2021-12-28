#include "CCircle.h"

void CCircle::Start()
{
}

void CCircle::Input(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
		x += 0.1;
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
		x -= 0.1;
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		y += 0.1;
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
		y -= 0.1;
}

void CCircle::Update()
{
	Render();
}

void CCircle::Render()
{
	glColor3f(r, g, b);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		float rad = i * (3.141592654 / 180);
		// 3f is 3d hence 0 z
		// Transformation Matrix + Translation
		glVertex3f((cos(rad) * 1.f) + x, (sin(rad) * 1.f) + y, 0);
	}
	glEnd();
}
