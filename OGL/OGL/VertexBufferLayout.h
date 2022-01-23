#pragma once
#include "NumptyBehavior.h"

struct VertexBufferElement
{
	static unsigned int GetSizeOfType(unsigned int Type)
	{
		switch (Type)
		{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_BYTE: return 1;
		}
		return 0;
	}

	unsigned int Type;
	unsigned int Count;
	bool Normalized;
};

class VertexBufferLayout
{
public:
	VertexBufferLayout()
		:m_Stride(0)
	{
	}

	template <typename T>
	void Push(int Count)
	{
		static_assert(false);
	}

	template <>
	void Push<float>(int Count)
	{
		VertexBufferElement element;
		element.Type = GL_FLOAT;
		element.Count = Count;
		element.Normalized = GL_FALSE;
		m_Elements.push_back(element);
		m_Stride += Count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template <>
	void Push<glm::vec4>(int Count)
	{
		VertexBufferElement element;
		element.Type = GL_FLOAT;
		element.Count = Count;
		element.Normalized = GL_FALSE;
		m_Elements.push_back(element);
		m_Stride += Count * sizeof(glm::vec4);
	}

	inline GLuint GetStride() const { return m_Stride; }
	inline const std::vector<VertexBufferElement>& GetElements() { return m_Elements; }
private:
	std::vector<VertexBufferElement> m_Elements;
	GLuint m_Stride;
};

