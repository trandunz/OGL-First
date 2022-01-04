#pragma once
#include "CShape.h"

class CProp :
    public CShape
{
public:
    CProp();
    ~CProp();

	void Start() { 
		UpdateVertexPositions(m_Position.x, m_Position.y, m_Position.z);
		ShaderNonsense();
	};

    void Update() { Render(); };
    void Render() {
        glUseProgram(m_ShaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
    };

	void ShaderNonsense()
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
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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
	}

	bool UpdateVertexPositions(float _x, float _y, float _z)
	{
		bool moved = false;
		if (_x >= 0.000000001 || _x <= -0.000000001)
		{
			vertices[0] += _x;
			vertices[3] += _x;
			vertices[6] += _x;
			vertices[9] += _x;
			vertices[12] += _x;
			vertices[15] += _x;
			moved = true;
		}
		if (_y >= 0.000000001 || _y <= -0.000000001)
		{
			vertices[1] += _y;
			vertices[4] += _y;
			vertices[7] += _y;
			vertices[10] += _y;
			vertices[13] += _y;
			vertices[16] += _y;
			moved = true;
		}
		if (_z >= 0.000000001 || _z <= -0.000000001)
		{
			vertices[2] += _z;
			vertices[5] += _z;
			vertices[8] += _z;
			vertices[11] += _z;
			vertices[14] += _z;
			vertices[17] += _z;
			moved = true;
		}

		return moved;
	}

private:
	// Vertices coordinates
	GLfloat vertices[24] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,	// Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,		// Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,	// Upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,	// Inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,	// Inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,		// Inner down
	};

	// Indices for vertices order
	GLuint indices[9] =
	{
		0, 3, 5, // Lower left triangle
		3, 2, 4, // Lower right triangle
		5, 4, 1 // Upper triangle
	};

    float m_Mass = 1.0f;
    Vector3 m_Velocity;
    Vector3 m_Position;
};

