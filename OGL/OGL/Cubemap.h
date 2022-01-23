#pragma once
#include "NumptyBehavior.h"
#include "Shader.h"
#include "CCamera.h"
class Cubemap :
    public NumptyBehavior
{
public:
	Cubemap(Camera& camera);
	~Cubemap()
	{
		CleanupPointer(skyboxShader);
		camera = nullptr;
	}

	void Bind();
	void Start(Camera& _camera)
	{
		CleanupPointer(camera);
		camera = &_camera;
	}
	void Render();
	void Unbind();
	void Delete();

	GLuint ID;
	GLenum Type;
	Shader* skyboxShader = nullptr;
	Camera* camera = nullptr;
private:
	unsigned int cubemapTexture;
	unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)1920.0f / 1080.0f, 0.1f, 100.0f);

	float skyboxVertices[25] =
	{
		//   Coordinates
		-1.0f, -1.0f,  1.0f,//        7--------6
		 1.0f, -1.0f,  1.0f,//       /|       /|
		 1.0f, -1.0f, -1.0f,//      4--------5 |
		-1.0f, -1.0f, -1.0f,//      | |      | |
		-1.0f,  1.0f,  1.0f,//      | 3------|-2
		 1.0f,  1.0f,  1.0f,//      |/       |/
		 1.0f,  1.0f, -1.0f,//      0--------1
		-1.0f,  1.0f, -1.0f
	};

	unsigned int skyboxIndices[36] =
	{
		// Right
		1, 2, 6,
		6, 5, 1,
		// Left
		0, 4, 7,
		7, 3, 0,
		// Top
		4, 5, 6,
		6, 7, 4,
		// Bottom
		0, 3, 2,
		2, 1, 0,
		// Back
		0, 1, 5,
		5, 4, 0,
		// Front
		3, 7, 6,
		6, 2, 3
	};
};

