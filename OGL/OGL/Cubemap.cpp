#include <stb-master/stb_image.h>
#define STB_IMAGE_IMPLEMENTATION

#include "Cubemap.h"

namespace Harmony
{
	Cubemap::Cubemap(Camera& _camera)
	{
		m_Camera = &_camera;
		m_ShaderID = CShaderLoader::CreateShader("Resources/Shaders/skybox.vs", "", "Resources/Shaders/skybox.fs");
		glUseProgram(m_ShaderID);
		glUniform1i(glGetUniformLocation(m_ShaderID, "skybox"), 0);

		// Create VAO, VBO, and EBO for the skybox
		glGenVertexArrays(1, &m_VertexArrayID);
		glGenBuffers(1, &m_VertexBufferID);
		glGenBuffers(1, &m_IndexBufferID);
		glBindVertexArray(m_VertexArrayID);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), &skyboxIndices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// All the faces of the cubemap (make sure they are in this exact order)
		std::string facesCubemap[6] =
		{
			"Resources/Textures/Skybox/right.jpg",
			"Resources/Textures/Skybox/left.jpg",
			"Resources/Textures/Skybox/top.jpg",
			"Resources/Textures/Skybox/bottom.jpg",
			"Resources/Textures/Skybox/front.jpg",
			"Resources/Textures/Skybox/back.jpg",
		};

		// Creates the cubemap texture object
		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureID);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		// These are very important to prevent seams
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		// This might help with seams on some systems
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
		stbi_set_flip_vertically_on_load(true);

		// Cycles through all the textures and attaches them to the cubemap object
		for (unsigned int i = 0; i < 6; i++)
		{
			int width, height, nrChannels;
			unsigned char* data = stbi_load(facesCubemap[i].c_str(), &width, &height, &nrChannels, 0);
			if (data)
			{
				stbi_set_flip_vertically_on_load(false);
				glTexImage2D
				(
					GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0,
					GL_RGB,
					width,
					height,
					0,
					GL_RGB,
					GL_UNSIGNED_BYTE,
					data
				);
				stbi_image_free(data);
			}
			else
			{
				Print("Failed to load texture: " + facesCubemap[i] );
				stbi_image_free(data);
			}
		}
		glUseProgram(0);
	}

	void Cubemap::Render()
	{
		// Enable Skybox Depth Testing
		glDepthFunc(GL_LEQUAL);
		glUseProgram(m_ShaderID);
		
		projection = m_Camera->GetProjectionMatrix();
		view = m_Camera->GetViewMatrix();
		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Camera->Position);
		glUniformMatrix4fv(glGetUniformLocation(m_ShaderID, "view"), 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(m_ShaderID, "model"), 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(m_ShaderID, "projection"), 1, GL_FALSE, &projection[0][0]);

		glBindVertexArray(m_VertexArrayID);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureID);

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		// Unbind
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		glUseProgram(0);

		// Enable Default Depth Testing
		glDepthFunc(GL_LESS);
	}
}
