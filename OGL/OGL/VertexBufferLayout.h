#pragma once
#include "NumptyBehavior.h"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	bool normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_BYTE: return 1;
		}
		return 0;
	}
};

class VertexBufferLayout
{
public:
	VertexBufferLayout()
		:m_Stride(0)
	{
	}

	template <typename T>
	void Push(int count)
	{
		static_assert(false);
	}

	template <>
	void Push<float>(int count)
	{
		VertexBufferElement element;
		element.type = GL_FLOAT;
		element.count = count;
		element.normalized = GL_FALSE;
		m_Elements.push_back(element);
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}
	//void Push< unsigned int >(int count)
	//{
	//	VertexBufferElement element;
	//	element.type = GL_UNSIGNED_INT;
	//	element.count = count;
	//	element.normalized = GL_FALSE;
	//	m_Elements.push_back(element);
	//	m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	//}
	//void Push<unsigned char>(int count)
	//{
	//	VertexBufferElement element;
	//	element.type = GL_UNSIGNED_BYTE;
	//	element.count = count;
	//	element.normalized = GL_TRUE;
	//	m_Elements.push_back(element);
	//	m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	//}


	inline unsigned int GetStride() const { return m_Stride; }
	inline const std::vector<VertexBufferElement>& GetElements() { return m_Elements; }
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
};

