#pragma once
#include "CCamera.h"
#include "TextureMaster.h"
#include "GUI.h"
#include "Physics.h"

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

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

		void HandleCollision()
		{
			std::vector<bool> intersections = Intersects();
			for (int i = 0; i < m_InstanceMatrix.size(); i++)
			{
				if (intersections[i])
				{
					m_InstanceMatrix[i] = m_PreviousPositions[i];
				}
			}
		}
		int GetInstanceMatrixSize();

		bool Contains(glm::vec3 _point);
		std::vector<bool> Intersects();

		bool m_LightingEnabled = false;
	private:
		glm::mat4 ModifyModelTransformations(glm::mat4& _model, STransform _transform);
		glm::mat4 CalculateModelTransformations(glm::mat4& _model, STransform& _transform);
		std::vector<float> BuildSphereUnitPositiveX(int _subDivisions);
		std::vector<float> BuildSphereUnitNegativeX(int _subDivisions);
		void BuildNormals(std::string _shapeType = "Square");
		void BuildVertexPoints(std::string _shapeType = "Square");
		
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
		std::vector<glm::mat4> m_PreviousPositions;
		glm::mat4 m_ProjectionMat{};
		glm::mat4 m_ViewMat{};

		std::vector<Vertex> m_Vertices;
		std::vector<unsigned int> m_Indices;
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
