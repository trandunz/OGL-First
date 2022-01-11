#include "CShape.h"

using namespace Shape;



void CShape::SetMVPUniform(Transform _transform)
{
	proj = glm::perspective(glm::radians(m_Camera->Zoom), 1920.0f / 1080.0f, 0.1f, 100.0f);
	CalculateModelTransformations(model, _transform);
	view = m_Camera->GetViewMatrix();
	glm::mat4 mvp = proj * view * model;
	m_Shader->SetUniformMat4f("u_MVP", mvp);
}

void CShape::SetMVPUniform()
{
	proj = glm::perspective(glm::radians(m_Camera->Zoom), 1920.0f / 1080.0f, 0.1f, 100.0f);
	CalculateModelTransformations(model, transform);
	view = m_Camera->GetViewMatrix();
	glm::mat4 mvp = proj * view * model;
	m_Shader->SetUniformMat4f("u_MVP", mvp);
}

void CShape::SetMVPUniform(Shader* _shader, Transform _transform)
{
	proj = glm::perspective(glm::radians(m_Camera->Zoom), 1920.0f / 1080.0f, 0.1f, 100.0f);
	CalculateModelTransformations(model, _transform);
	view = m_Camera->GetViewMatrix();
	_shader->SetUniformMat4f("projection", proj);
	_shader->SetUniformMat4f("model", model);
	_shader->SetUniformMat4f("view", view);
}

bool CShape::UpdatePosition(float _x, float _y, float _z)
{
	bool moved = false;
	if (_x >= 0.000000001 || _x <= -0.000000001)
	{
		transform.position.x += _x;
		moved = true;
	}
	if (_y >= 0.000000001 || _y <= -0.000000001)
	{
		transform.position.y += _y;
		moved = true;
	}
	if (_z >= 0.000000001 || _z <= -0.000000001)
	{
		transform.position.z += _z;
		moved = true;
	}

	return moved;
}

void CShape::CreateVBBasedOnType()
{
	CleanupPointer(m_VertBuffer);
	switch (ShapeType)
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
	switch (ShapeType)
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
