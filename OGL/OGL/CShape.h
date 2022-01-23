#pragma once
#include "SHAPEARRAYS.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "CCamera.h"

namespace Shape
{
	enum class TYPE
	{
		UNASSIGNED = 0,

		SQUARE,
		TRIANGLE,
		CIRCLE,
		CUBE,
		SPHERE,
	};

	class CShape : public NumptyBehavior
	{
	public:
		inline void SetType(TYPE _type) { m_ShapeType = _type; }
		inline bool GetWireFrameMode() { return m_WireFrameMode; }
		inline VertexBuffer* GetVertexBuffer(){ return m_VertBuffer; }

		virtual ~CShape();

		glm::mat4 CalculateModelTransformations(glm::mat4& _model, STransform _transform);

		void SetMVPUniform();
		void SetMVPUniform(STransform _transform);
		void SetMVPUniform(Shader* _shader, STransform _transform);
		bool UpdatePosition(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f);

		bool MarkAsDestroy = false;
		STransform Transform;

	protected:
		Shader* m_Shader = nullptr;
		Shader* m_InstanceShader = nullptr;
		Shader* m_LightingShader = nullptr;
		Renderer m_Renderer;
		Camera* m_Camera = nullptr;

		VertexBuffer* m_VertBuffer = nullptr;
		VertexBuffer* m_InstanceBuffer = nullptr;
		IndexBuffer* m_IndexBuffer = nullptr;
		VertexArray* m_VertexArray = nullptr;

		TYPE m_ShapeType;
		SHAPEARRAYS m_ShapeArrays;
		std::vector<glm::mat4> m_InstanceMatrix;
		unsigned int m_InstanceCount = 0;

		glm::mat4 m_ProjectionMat = glm::perspective(45.0f, (float)1920.0f / (float)1080.0f, 0.0f, 4000.0f);
		glm::mat4 m_ViewMat = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -2));
		glm::mat4 m_ModelMat = glm::translate(glm::mat4(1.0f), Transform.position);

		// Indices for vertices order
		GLuint m_Indices[256]{};

		// Vertices coordinates
		GLfloat m_Vertices[256]{};

		DirLight m_DirectionalLights[256]{};
		PointLight m_PointLights[256]{};
		SpotLight m_SpotLights[256]{};

		glm::vec3 m_InputVec;

		glm::vec4 m_RGBA_Copy = { 1,0,0,1 };

		float m_Color[4] = { 1,0,0,1 };
		float m_dt = 0.0f;

		bool m_WireFrameMode = false;

		void CreateInstance(STransform _transform);
		void CreateVBBasedOnType();
		void CreateIBBasedOnType();
	};
}

