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
		CUBE,
		SPHERE,
    };

    void SetType(SHAPETYPE _type)
    {
        ShapeType = _type;
    }
	inline void SetMVPUniform(glm::vec3 _position)
	{
		proj = glm::perspective(glm::radians(m_Camera->Zoom), 1920.0f / 1080.0f, 0.1f, 100.0f);
		model = glm::translate(glm::mat4(1.0f), _position);
		view = m_Camera->GetViewMatrix();
		glm::mat4 mvp = proj * view * model;
		m_Shader->SetUniformMat4f("u_MVP", mvp);
	}
	inline void SetMVPUniform()
	{
		proj = glm::perspective(glm::radians(m_Camera->Zoom), 1920.0f / 1080.0f, 0.1f, 100.0f);
		model = glm::translate(glm::mat4(1.0f), m_Position);
		view = m_Camera->GetViewMatrix();
		glm::mat4 mvp = proj * view * model;
		m_Shader->SetUniformMat4f("u_MVP", mvp);
	}
	inline void SetMVPUniform(Shader* _shader)
	{
		proj = glm::perspective(glm::radians(m_Camera->Zoom), 1920.0f / 1080.0f, 0.1f, 100.0f);
		model = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
		view = m_Camera->GetViewMatrix();
		_shader->SetUniformMat4f("projection", proj);
		_shader->SetUniformMat4f("model", model);
		_shader->SetUniformMat4f("view", view);
	}

	bool MARKASDESTROY = false;

	VertexBuffer* GetVertexBuffer()
	{
		return m_VertBuffer;
	}

protected:
    Shader* m_Shader = nullptr;
	Shader* m_LightingShader = nullptr;
    Renderer m_Renderer;
	Camera* m_Camera = nullptr;

	VertexBuffer* m_VertBuffer = nullptr;
	IndexBuffer* m_IndexBuffer = nullptr;
	VertexArray* m_VertexArray = nullptr;

	glm::mat4 proj = glm::perspective(45.0f, (float)1920.0f / (float)1080.0f, 0.0f, 4000.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -2));
	glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Position);

	glm::vec3 m_Position = { 0, 0, -10 };

    // Vertices coordinates
    GLfloat m_Vertices[256]{};

    // Indices for vertices order
    GLuint m_Indices[256]{};

	SHAPETYPE ShapeType;

    float m_Scale = 1.0f;

    glm::vec3 m_InputVec;

	glm::vec4 m_RGBA_Copy = { 1,0,0,1 };
	float m_Color[4] = { 1,0,0,1 };

	float m_dt = 0.0f;

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

			float cube[] = {
				-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
				 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
				 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
				 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
				-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
				-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

				-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
				 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
				 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
				 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
				-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
				-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

				-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
				-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
				-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
				-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
				-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
				-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

				 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
				 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
				 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
				 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
				 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
				 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

				-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
				 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
				 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
				 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
				-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
				-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

				-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
				 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
				 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
				 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
				-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
				-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
			};
			m_VertBuffer = new VertexBuffer(cube, sizeof(cube)); // 4 x 4 vertices
			break;
		}
		case SHAPETYPE::SPHERE:
		{

			float cube[] = {
				-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
				 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
				 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
				 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
				-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
				-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

				-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
				 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
				 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
				 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
				-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
				-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

				-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
				-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
				-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
				-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
				-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
				-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

				 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
				 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
				 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
				 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
				 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
				 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

				-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
				 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
				 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
				 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
				-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
				-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

				-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
				 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
				 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
				 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
				-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
				-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
			};
			m_VertBuffer = new VertexBuffer(cube, sizeof(cube)); // 4 x 4 vertices
			break;
		}
		case SHAPETYPE::TRIANGLE:
		{
			GLfloat triangle[12]{
							 0.5f,  0.5f,	0.0f, 0.0f,
							 0.5f, -0.5f,	1.0f, 0.0f,
							-0.5f, -0.5f,	1.0f, 1.0f,
			};
			m_VertBuffer = new VertexBuffer(triangle, sizeof(triangle)); // 4 x 4 vertices
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

