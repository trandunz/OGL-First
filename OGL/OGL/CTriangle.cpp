#include "CTriangle.h"

CTriangle::~CTriangle()
{

}

void CTriangle::Start()
{
	m_ShaderProgram = CShaderLoader::CreateShaderProgram("Resources/Shaders/TriangleShader.vs", "Resources/Shaders/TriangleShader.fs");
	glGenBuffers(1, &VAO);

	glGenBuffers(1, &VBO);
	// 1. bind Vertex Array Object
	glBindVertexArray(VAO);
	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
}

void CTriangle::Input(GLFWwindow* window, int key, int scancode, int action, int mods)
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

void CTriangle::Update()
{
	Render();
}

void CTriangle::Render()
{
	glUseProgram(m_ShaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
