#pragma once
#include "NumptyBehavior.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

class CShape :	public NumptyBehavior
{
public:
    virtual ~CShape()
    {
        CleanupPointer(m_Shader);
		CleanupPointer(m_VertBuffer);
		CleanupPointer(m_IndexBuffer);
		CleanupPointer(m_VertexArray);
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
        CIRCLE
    };

    void SetType(SHAPETYPE _type)
    {
        ShapeType = _type;
    }

protected:
    Shader* m_Shader;
    Renderer m_Renderer;

	VertexBuffer* m_VertBuffer = nullptr;
	IndexBuffer* m_IndexBuffer = nullptr;
	VertexArray* m_VertexArray = nullptr;

    // Vertices coordinates
    GLfloat m_Vertices[32]{};

    // Indices for vertices order
    GLuint m_Indices[32]{};

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
			for (int i = 0; i < 16; i++)
			{
				m_Vertices[i] = square[i];
			}
			m_VertBuffer = new VertexBuffer(m_Vertices, 4 * 4 * sizeof(float)); // 4 x 4 vertices
			break;
		}

		case SHAPETYPE::TRIANGLE:
		{
			GLfloat triangle[12]{
							 0.5f,  0.5f,	0.0f, 0.0f,
							 0.5f, -0.5f,	1.0f, 0.0f,
							-0.5f, -0.5f,	1.0f, 1.0f,
			};
			for (int i = 0; i < 12; i++)
			{
				m_Vertices[i] = triangle[i];
			}
			m_VertBuffer = new VertexBuffer(m_Vertices, 3 * 4 * sizeof(float)); // 4 x 4 vertices
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
			GLfloat square[6]{
				0, 1, 2, // Lower left triangle
				2, 3, 0, // Lower right triangle
			};
			for (int i = 0; i < 6; i++)
			{
				m_Indices[i] = square[i];
			}
			m_IndexBuffer = new IndexBuffer(m_Indices, 6);
			break;
		}

		case SHAPETYPE::TRIANGLE:
		{
			GLfloat triangle[3]{
				0, 1, 2, // Lower left triangle
			};
			for (int i = 0; i < 3; i++)
			{
				m_Indices[i] = triangle[i];
			}
			m_IndexBuffer = new IndexBuffer(m_Indices, 3);
			break;
		}

		default:
			break;
		}
	}
};

