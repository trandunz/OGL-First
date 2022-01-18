#include "CShape.h"

using namespace Shape;
	void CShape::SetMVPUniform(STransform _transform)
	{
		m_ProjectionMat = glm::perspective(glm::radians(m_Camera->Zoom), 1920.0f / 1080.0f, 0.1f, 100.0f);
		CalculateModelTransformations(m_ModelMat, _transform);
		m_ViewMat = m_Camera->GetViewMatrix();
		glm::mat4 mvp = m_ProjectionMat * m_ViewMat * m_ModelMat;
		m_Shader->SetUniformMat4f("u_MVP", mvp);
	}

	CShape::~CShape()
	{
		m_Camera = nullptr;
		m_Shader = nullptr;
		m_VertBuffer = nullptr;
		m_IndexBuffer = nullptr;
		m_VertexArray = nullptr;
	}

	glm::mat4 CShape::CalculateModelTransformations(glm::mat4& _model, STransform _transform)
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

	void CShape::SetMVPUniform()
	{
		m_ProjectionMat = glm::perspective(glm::radians(m_Camera->Zoom), 1920.0f / 1080.0f, 0.1f, 100.0f);
		CalculateModelTransformations(m_ModelMat, Transform);
		m_ViewMat = m_Camera->GetViewMatrix();
		glm::mat4 mvp = m_ProjectionMat * m_ViewMat * m_ModelMat;
		m_Shader->SetUniformMat4f("u_MVP", mvp);
	}

	void CShape::SetMVPUniform(Shader* _shader, STransform _transform)
	{
		m_ProjectionMat = glm::perspective(glm::radians(m_Camera->Zoom), 1920.0f / 1080.0f, 0.1f, 100.0f);
		CalculateModelTransformations(m_ModelMat, _transform);
		m_ViewMat = m_Camera->GetViewMatrix();
		_shader->SetUniformMat4f("projection", m_ProjectionMat);
		_shader->SetUniformMat4f("model", m_ModelMat);
		_shader->SetUniformMat4f("view", m_ViewMat);
	}

	bool CShape::UpdatePosition(float _x, float _y, float _z)
	{
		bool moved = false;
		if (_x >= 0.000000001 || _x <= -0.000000001)
		{
			Transform.position.x += _x;
			moved = true;
		}
		if (_y >= 0.000000001 || _y <= -0.000000001)
		{
			Transform.position.y += _y;
			moved = true;
		}
		if (_z >= 0.000000001 || _z <= -0.000000001)
		{
			Transform.position.z += _z;
			moved = true;
		}

		return moved;
	}

	void CShape::CreateVBBasedOnType()
	{
		CleanupPointer(m_VertBuffer);
		switch (m_ShapeType)
		{
		case TYPE::SQUARE:
		{
			m_VertBuffer = new VertexBuffer(m_ShapeArrays.VERT_SQUARE, sizeof(m_ShapeArrays.VERT_SQUARE)); // 4 x 4 vertices
			break;
		}
		case TYPE::CUBE:
		{
			m_VertBuffer = new VertexBuffer(m_ShapeArrays.VERT_CUBE, sizeof(m_ShapeArrays.VERT_CUBE)); // 4 x 4 vertices
			break;
		}
		case TYPE::SPHERE:
		{
			m_VertBuffer = new VertexBuffer(m_ShapeArrays.VERT_CUBE, sizeof(m_ShapeArrays.VERT_CUBE)); // 4 x 4 vertices
			break;
		}
		case TYPE::TRIANGLE:
		{
			m_VertBuffer = new VertexBuffer(m_ShapeArrays.VERT_TRIANGLE, sizeof(m_ShapeArrays.VERT_TRIANGLE)); // 4 x 4 vertices
			break;
		}
		default:
			break;
		}
	}

	void CShape::CreateIBBasedOnType()
	{
		CleanupPointer(m_IndexBuffer);
		switch (m_ShapeType)
		{
		case TYPE::SQUARE:
		{
			m_IndexBuffer = new IndexBuffer(m_ShapeArrays.INDEX_SQUARE, 6);
			break;
		}

		case TYPE::CUBE:
		{
			m_IndexBuffer = new IndexBuffer(m_ShapeArrays.INDEX_CUBE, 36);
			break;
		}

		case TYPE::TRIANGLE:
		{
			m_IndexBuffer = new IndexBuffer(m_ShapeArrays.INDEX_TRIANGLE, 3);
			break;
		}
		default:
			break;
		}
	}


