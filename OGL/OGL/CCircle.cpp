#include "CCircle.h"

CCircle::~CCircle()
{
}

void CCircle::Start()
{

	m_ShaderProgram = CShaderLoader::CreateShaderProgram("Resources/Shaders/TriangleShader.vs", "Resources/Shaders/TriangleShader.fs");
	glGenBuffers(1, &VAO);

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// 1. bind Vertex Array Object
	glBindVertexArray(VAO);
	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Bind the EBO specifying it's a GL_ELEMENT_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// Introduce the indices into the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);

	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	// Bind the EBO to 0 so that we don't accidentally modify it
	// MAKE SURE TO UNBIND IT AFTER UNBINDING THE VAO, as the EBO is linked in the VAO
	// This does not apply to the VBO because the VBO is already linked to the VAO during glVertexAttribPointer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void CCircle::Input(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	/*if (key == GLFW_KEY_D && action == GLFW_PRESS)
		x += 0.1;
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
		x -= 0.1;
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		y += 0.1;
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
		y -= 0.1;*/
}

void CCircle::Update()
{
	Render();
}

void CCircle::Render()
{
	int numberOfVertices = 10 + 2;

	GLfloat twicePi = 2.0f * 3.141592654;

	GLfloat circleVerticesX[12]{};
	GLfloat circleVerticesY[12]{};
	GLfloat circleVerticesZ[12]{};

	circleVerticesX[0] = x;
	circleVerticesY[0] = y;
	circleVerticesZ[0] = z;

	for (int i = 1; i < numberOfVertices; i++)
	{
		circleVerticesX[i] = x + (120 * cos(i * twicePi / 10));
		circleVerticesY[i] = y + (120 * sin(i * twicePi / 10));
		circleVerticesZ[i] = z;
	}

	GLfloat allCircleVertices[(13) * 3];

	for (int i = 0; i < numberOfVertices; i++)
	{
		allCircleVertices[i * 3] = circleVerticesX[i];
		allCircleVertices[(i * 3) + 1] = circleVerticesY[i];
		allCircleVertices[(i * 3) + 2] = circleVerticesZ[i];
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, allCircleVertices);
	glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfVertices);
	glDisableClientState(GL_VERTEX_ARRAY);
}
