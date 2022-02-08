#pragma once
#include "CCamera.h"
#include "TextureMaster.h"
#include "GUI.h"
#include "Physics.h"

namespace Harmony
{
	class Mesh
	{
	public:
		Mesh(Camera& _camera, TextureMaster& _textureMaster);
		~Mesh();

		void RAW_Recompile();
		void RAW_Compile();

		void RAW_Draw();
		void ImGuiHandler();

		void CreateInstance(STransform _transform = STransform{ {0,0,0} ,{0,0,0}, {1,1,1},0 });
		void ModifyInstanceMatrix(unsigned int _index, STransform _transform);
		void ModifyInstance(unsigned int _index, STransform _transform);
		void ModifyInstance(unsigned int _index, float _color[4]);

		int GetInstanceMatrixSize();

		bool Contains(glm::vec3 _point);

		bool m_LightingEnabled = false;
	private:
		glm::mat4 ModifyModelTransformations(glm::mat4& _model, STransform _transform);
		glm::mat4 CalculateModelTransformations(glm::mat4& _model, STransform _transform);
		std::vector<float> BuildSphereUnitPositiveX(int _subDivisions);
		std::vector<float> BuildSphereUnitNegativeX(int _subDivisions);
		
		Camera* m_Camera = nullptr;
		TextureMaster* m_TextureMaster = nullptr;

		unsigned int m_ShaderID;
		unsigned int m_VertexArrayID;
		unsigned int m_VertBufferID;
		unsigned int m_InstanceBufferID;
		unsigned int m_IndexBufferID;
		unsigned int m_UniformBufferID;

		unsigned int m_InstanceCount = 0;

		float m_Color[4]{ 1,1,1,1 };

		std::vector<glm::mat4> m_InstanceMatrix;
		glm::mat4 m_ProjectionMat{};
		glm::mat4 m_ViewMat{};

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
			0, 1, 2,
			2, 4, 0,

			6, 7, 8,
			8, 10, 6,

			12, 13, 14,
			14, 16, 12,

			18, 19, 20,
			20, 22, 18,

			24, 25, 26,
			26, 28, 24,

			30, 31, 32,
			32, 34, 30
		};
	};
}
