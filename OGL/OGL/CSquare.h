#pragma once
#include "CProp.h"
class CSquare :
	public CProp
{
public:
	std::map<int, bool>* keypresses = nullptr;
	CSquare(std::map<int, bool>& _keyMap)
	{
		keypresses = &_keyMap;
	};
	virtual ~CSquare() {
		keypresses = nullptr;
	};

	virtual void Start() override {
	};
	virtual void Update(long double _dt){
		glPushMatrix();
		//
		glTranslatef(halfScreenWidth, halfScreenHeight, -500);
		glRotatef(rotationX, 1, 0, 0);
		glRotatef(rotationY, 0, 1, 0);

		glTranslatef(-halfScreenWidth, -halfScreenHeight, 500);

		DrawCircle(halfScreenWidth, halfScreenHeight, 0, 120, 36);
		DrawCube(halfScreenWidth, halfScreenHeight, -500, 200);
		DrawSphere();
		//
		glPopMatrix();
	};
	virtual void Render() override {
	};

	void Input(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		for (auto& item : (*keypresses))
		{
			if (item.second == true)
			{
				switch (item.first)
				{
				case GLFW_KEY_UP:
					rotationX -= rotationSpeed;
					break;
				case GLFW_KEY_DOWN:
					rotationX += rotationSpeed;
					break;
				case GLFW_KEY_RIGHT:
					rotationY += rotationSpeed;
					break;
				case GLFW_KEY_LEFT:
					rotationY -= rotationSpeed;
					break;
				default:
					break;
				}
			}
		}
	}

	virtual void ShaderNonsense() override
	{
		if (m_ShaderProgram)
		{
			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
			glDeleteBuffers(1, &EBO);

			glDeleteVertexArrays(0, &VAO);
			glDeleteBuffers(0, &VBO);
			glDeleteBuffers(0, &EBO);

			glDeleteProgram(m_ShaderProgram);
		}

		m_ShaderProgram = CShaderLoader::CreateShaderProgram("Resources/Shaders/TriangleShader.vs", "Resources/Shaders/TriangleShader.fs");
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		// Make the VAO the current Vertex Array Object by binding it
		glBindVertexArray(VAO);

		// Bind the VBO specifying it's a GL_ARRAY_BUFFER
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// Introduce the vertices into the VBO
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vert_vertices), Vert_vertices, GL_STATIC_DRAW);

		// Bind the EBO specifying it's a GL_ELEMENT_ARRAY_BUFFER
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		// Introduce the indices into the EBO
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		// Enable the Vertex Attribute so that OpenGL knows to use it
		glEnableVertexAttribArray(0);

		// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		// Bind the EBO to 0 so that we don't accidentally modify it
		// MAKE SURE TO UNBIND IT AFTER UNBINDING THE VAO, as the EBO is linked in the VAO
		// This does not apply to the VBO because the VBO is already linked to the VAO during glVertexAttribPointer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	};

	void DrawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides)
	{
		GLint numberOfVertices = numberOfSides + 1;

		GLfloat doublePi = 2.0f * 3.14159265;

		GLfloat* circleVerticesX = new GLfloat[numberOfVertices];
		GLfloat* circleVerticesY = new GLfloat[numberOfVertices];
		GLfloat* circleVerticesZ = new GLfloat[numberOfVertices];

		//circleVerticesX[0] = x;
		//circleVerticesY[0] = y;
		//circleVerticesZ[0] = z;

		for (int i = 0; i < numberOfVertices; i++)
		{
			circleVerticesX[i] = x + (radius * cos(i * doublePi / numberOfSides));
			circleVerticesY[i] = y + (radius * sin(i * doublePi / numberOfSides));
			circleVerticesZ[i] = z;
		}

		GLfloat* allCircleVertices = new GLfloat[numberOfVertices * 3];

		for (int i = 0; i < numberOfVertices; i++)
		{
			allCircleVertices[i * 3] = circleVerticesX[i];
			allCircleVertices[(i * 3) + 1] = circleVerticesY[i];
			allCircleVertices[(i * 3) + 2] = circleVerticesZ[i];
		}

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, allCircleVertices);
		glDrawArrays(GL_LINE_STRIP, 0, numberOfVertices);
		glDisableClientState(GL_VERTEX_ARRAY);

		delete[] circleVerticesX;
		delete[] circleVerticesY;
		delete[] circleVerticesZ;
		delete[] allCircleVertices;

		circleVerticesX = nullptr;
		circleVerticesY = nullptr;
		circleVerticesZ = nullptr;
		allCircleVertices = nullptr;
	}

	void DrawCube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength)
	{
		GLfloat halfSideLength = edgeLength * 0.5f;

		GLfloat vertices[] =
		{
			// front face
			centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
			centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top right
			centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom right
			centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left

			// back face
			centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top left
			centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
			centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
			centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom left

			// left face
			centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
			centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
			centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
			centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left

			// right face
			centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
			centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
			centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
			centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left

			// top face
			centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
			centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
			centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // bottom right
			centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // bottom left

			// top face
			centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // top left
			centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // top right
			centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
			centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength  // bottom left
		};

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glColor3f( colour[0], colour[1], colour[2] );
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, vertices);

		glDrawArrays(GL_QUADS, 0, 24);

		glDisableClientState(GL_VERTEX_ARRAY);
	}

	void DrawSphere()
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, Vert_vertices);
		glDrawArrays(GL_POLYGON, 0, 5);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
protected:

	GLfloat halfScreenWidth = 1920 / 2;
	GLfloat halfScreenHeight = 1080 / 2;

	GLfloat rotationX = 0.0f;
	GLfloat rotationY = 0.0f;
	const GLfloat rotationSpeed = 1;

	// Vertices coordinates
	GLfloat Vert_vertices[15] =
	{
		20, 100, 0,
		100, 300, 0,
		500, 50, 0,
		320, 10, 0,
		40, 40, 0	// Inner down
	};

	// Indices for vertices order
	GLuint indices[9] =
	{
		0, 3, 5, // Lower left triangle
		3, 2, 4, // Lower right triangle
		5, 4, 1 // Upper triangle
	};
};

