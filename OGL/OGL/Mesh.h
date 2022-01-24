#pragma once
#include "NumptyBehavior.h"
#include "VertexBuffer.h"
#include "CCamera.h"
#include "Texture.h"
#include "Renderer.h"
#include "GUI.h"
#include "UniformBuffer.h"

class Mesh : public NumptyBehavior
{
public:
	enum class MESHTYPE
	{
		CUBE,
	};

	Mesh(Camera& _camera, MESHTYPE _type = MESHTYPE::CUBE);
	~Mesh();

	void Compile();
	void CompileShaders(const char* _vs, const char* _gs, const char* _fs);
	void CompileNormal(const char* _normalMap);
	void CompileTexture(std::string _defuse);

	void Draw();
	void ImGuiHandler();

	void CreateInstance(STransform _transform = STransform{ {0,0,0} ,{0,0,0}, {1,1,1},0 });
	void ModifyInstance(unsigned int _index, STransform _transform);
	void ModifyInstance(unsigned int _index, float _color[4]);

	bool m_LightingEnabled = true;
private:
	void HandleLightingUniforms();
	void SetMVPUniform(STransform _transform);
	glm::mat4 CalculateModelTransformations(glm::mat4& _model, STransform _transform);

	Renderer m_Renderer;
	Texture* m_Texture = nullptr;
	Texture* m_Normal = nullptr;
	Shader* m_Shader = nullptr;
	VertexBuffer* m_VertBuffer = nullptr;
	VertexBuffer* m_InstanceBuffer = nullptr;
	UniformBuffer* m_UniformBuffer = nullptr;
	IndexBuffer* m_IndexBuffer = nullptr;
	VertexArray* m_VertexArray = nullptr;

	std::vector<glm::mat4> m_InstanceMatrix;
	unsigned int m_InstanceCount = 0;
	unsigned int uboMatrices;
	unsigned int uboPLights;
	PointLight* m_PointLights = nullptr;

	MESHTYPE m_Type = MESHTYPE::CUBE;
	Camera* m_Camera = nullptr;

	glm::mat4 m_ProjectionMat{};
	glm::mat4 m_ViewMat{};
	glm::mat4 m_ModelMat{};

	float m_Color[4]{1,1,1,1};

	GLfloat VERT_CUBE[8 * 36] =
	{
		-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f, 	0.0f,  1.0f
	};

	GLuint INDEX_CUBE[36]
	{
		// -
		0, 1, 2,
		2, 4, 0,

		6, 7, 8, // -
		8, 10, 6,

		12, 13, 14, // -
		14, 16, 12,

		18, 19, 20, // 
		20, 22, 18,

		24, 25, 26, // 
		26, 28, 24,

		30, 31, 32, // 
		32, 34, 30
	};
};

