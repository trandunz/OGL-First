#pragma once
#include "NumptyBehavior.h"
#include "Shader.h"
#include "CCamera.h"

namespace Harmony
{
	class Cubemap : public NumptyBehavior
	{
	public:
		Cubemap(Camera& _camera);
		~Cubemap()
		{	
			// Unbind
			{
				glDeleteTextures(1, &m_TextureID);
				glBindTexture(m_TextureID, 0);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindVertexArray(0);
				glUseProgram(0);
			}
			// Delete
			{
				glDeleteVertexArrays(1, &m_VertexArrayID);
				glDeleteBuffers(1, &m_VertexBufferID);
				glDeleteBuffers(1, &m_IndexBufferID);
				glDeleteProgram(m_ShaderID);
			}
			m_Camera = nullptr;
		}

		void Render();

		
	private:
		Camera* m_Camera = nullptr;
		unsigned int m_ShaderID;
		unsigned int m_TextureID;
		unsigned int m_VertexArrayID;
		unsigned int m_VertexBufferID; 
		unsigned int m_IndexBufferID;

		glm::mat4 projection{1.0f};
		glm::mat4 view{ 1.0f };

		float skyboxVertices[25] =
		{
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f
		};

		unsigned int skyboxIndices[36] =
		{
			1, 2, 6,
			6, 5, 1,
			0, 4, 7,

			7, 3, 0,
			4, 5, 6,
			6, 7, 4,

			0, 3, 2,
			2, 1, 0,
			0, 1, 5,

			5, 4, 0,
			3, 7, 6,
			6, 2, 3
		};
	};
}

