#pragma once
#include "NumptyBehavior.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "CCamera.h"

class CShape :	public NumptyBehavior
{
public:
    virtual ~CShape()
    {
		m_Camera = nullptr;
		m_Shader = nullptr;
		m_VertBuffer = nullptr;
		m_IndexBuffer = nullptr;
		m_VertexArray = nullptr;

    }

    virtual void Start() = 0;
    virtual void Input(GLFWwindow* window, int key, int scancode, int action, int mods) {};
    virtual void Update(float _dt) {};
    virtual void Render() {};

    enum class SHAPETYPE
    {
        UNASSIGNED = 0,

        SQUARE,
        TRIANGLE,
        CIRCLE,
		CUBE
    };

    void SetType(SHAPETYPE _type)
    {
        ShapeType = _type;
    }

	bool MARKASDESTROY = false;

protected:
    Shader* m_Shader = nullptr;
    Renderer m_Renderer;
	Camera* m_Camera = nullptr;

	VertexBuffer* m_VertBuffer = nullptr;
	IndexBuffer* m_IndexBuffer = nullptr;
	VertexArray* m_VertexArray = nullptr;

    // Vertices coordinates
    GLfloat m_Vertices[128]{};

    // Indices for vertices order
    GLuint m_Indices[128]{};

	SHAPETYPE ShapeType;

    float m_Scale = 1.0f;

    glm::vec3 m_InputVec;

    void CreateVBBasedOnType()
    {
		CleanupPointer(m_VertBuffer);
		switch (ShapeType)
		{
		case SHAPETYPE::SQUARE:
		{
			GLfloat square[16]{
					-0.5f, -0.5f,	0.0f, 0.0f,
					 0.5f, -0.5f,	1.0f, 0.0f,
					 0.5f,  0.5f,	1.0f, 1.0f,
					-0.5f,  0.5f,	0.0f, 1.0f
			};
			m_VertBuffer = new VertexBuffer(square, 4 * 4 * sizeof(float)); // 4 x 4 vertices
			break;
		}
		case SHAPETYPE::CUBE:
		{

			GLfloat cube[40]{
					-0.5f, -0.5f,  0.5f,		0.0f, 0.0f,
					 0.5f, -0.5f,  0.5f,		1.0f, 0.0f,
					 0.5f,  0.5f,  0.5f,		1.0f, 1.0f,
					-0.5f,  0.5f,  0.5f,		0.0f, 1.0f,

					-0.5f, -0.5f,  -0.5f,		0.0f, 0.0f,
					 0.5f, -0.5f,  -0.5f,		1.0f, 0.0f,
					 0.5f,  0.5f,  -0.5f,		1.0f, 1.0f,
					-0.5f,  0.5f,  -0.5f,		0.0f, 1.0f
			};
			m_VertBuffer = new VertexBuffer(cube, 5 * 8 * sizeof(float)); // 5 x 4 vertices
			break;
		}
		case SHAPETYPE::TRIANGLE:
		{
			GLfloat triangle[12]{
							 0.5f,  0.5f,	0.0f, 0.0f,
							 0.5f, -0.5f,	1.0f, 0.0f,
							-0.5f, -0.5f,	1.0f, 1.0f,
			};
			m_VertBuffer = new VertexBuffer(triangle, 3 * 4 * sizeof(float)); // 4 x 4 vertices
			break;
		}

		default:
			break;
		}
    }

	void CreateIBBasedOnType()
	{
		CleanupPointer(m_IndexBuffer);
		switch (ShapeType)
		{
		case SHAPETYPE::SQUARE:
		{
			GLuint square[6]{
				0, 1, 2, // Lower left triangle
				2, 3, 0, // Lower right triangle
			};
			m_IndexBuffer = new IndexBuffer(square, 6);
			break;
		}

		case SHAPETYPE::CUBE:
		{
			GLuint cube[36]{
				0, 1, 2, // Lower left triangle
				2, 3, 0, // Lower right triangle

				0, 4, 5, // Lower left triangle
				5, 1, 0,

				5, 1, 2, // Lower left triangle
				2, 6, 5,

				6, 2, 3, // Lower left triangle
				3, 7, 6,

				5, 6, 7, // Lower left triangle
				7, 4, 5,

				7, 3, 0, // Lower left triangle
				0, 4, 7,
			};
			m_IndexBuffer = new IndexBuffer(cube, 36);
			break;
		}

		case SHAPETYPE::TRIANGLE:
		{
			GLuint triangle[3]{
				0, 1, 2, // Lower left triangle
			};
			m_IndexBuffer = new IndexBuffer(triangle, 3);
			break;
		}

		default:
			break;
		}
	}
};

