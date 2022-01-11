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
		inline void SetType(TYPE _type) { ShapeType = _type; }
		inline bool GetWireFrameMode() { return m_WireFrameMode; }
		inline VertexBuffer* GetVertexBuffer(){ return m_VertBuffer; }

		virtual ~CShape()
		{
			m_Camera = nullptr;
			m_Shader = nullptr;
			m_VertBuffer = nullptr;
			m_IndexBuffer = nullptr;
			m_VertexArray = nullptr;
		}

		glm::mat4 CalculateModelTransformations(glm::mat4& _model, Transform _transform)
		{
			_model = glm::translate(glm::mat4(1.0f), _transform.position);
			if (_transform.rotation.x != 0.0f)
			{
				_model = glm::rotate(_model, _transform.rotation.x, _transform.rotation);
			}
			if (_transform.rotation.y != 0.0f)
			{
				_model = glm::rotate(_model, _transform.rotation.y, _transform.rotation);
			}
			if (_transform.rotation.z != 0.0f)
			{
				_model = glm::rotate(_model, _transform.rotation.z, _transform.rotation);
			}
			_model = glm::scale(_model, _transform.scale);
			return _model;
		}
		void SetMVPUniform();
		void SetMVPUniform(Transform _transform);
		void SetMVPUniform(Shader* _shader, Transform _transform);
		bool UpdatePosition(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f);

		bool MARKASDESTROY = false;
		Transform transform;

	protected:
		Shader* m_Shader = nullptr;
		Shader* m_LightingShader = nullptr;
		Renderer m_Renderer;
		Camera* m_Camera = nullptr;

		VertexBuffer* m_VertBuffer = nullptr;
		IndexBuffer* m_IndexBuffer = nullptr;
		VertexArray* m_VertexArray = nullptr;

		TYPE ShapeType;
		SHAPEARRAYS m_ShapeArrays;

		glm::mat4 proj = glm::perspective(45.0f, (float)1920.0f / (float)1080.0f, 0.0f, 4000.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -2));
		glm::mat4 model = glm::translate(glm::mat4(1.0f), transform.position);

		// Indices for vertices order
		GLuint m_Indices[256]{};

		// Vertices coordinates
		GLfloat m_Vertices[256]{};

		glm::vec3 m_InputVec;

		glm::vec4 m_RGBA_Copy = { 1,0,0,1 };

		float m_Color[4] = { 1,0,0,1 };
		float m_dt = 0.0f;

		bool m_WireFrameMode = false;

		void CreateVBBasedOnType();
		void CreateIBBasedOnType();
	};
}

