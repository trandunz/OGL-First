#pragma once
#include "NumptyBehavior.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
class VertexArray :
    public NumptyBehavior
{
public:
    VertexArray()
    {
        glGenVertexArrays(1, &m_RendererID);
        glBindVertexArray(m_RendererID);
    }
    ~VertexArray()
    {
        UnBind();
        glDeleteVertexArrays(1, &m_RendererID);
    }

    inline void AddBuffer(const VertexBuffer& vb,  VertexBufferLayout& layout)
    {
        vb.Bind();
        const std::vector<VertexBufferElement>& elements = layout.GetElements();
        unsigned int offset = 0;
        for (unsigned int i = 0; i < elements.size(); i++)
        {
            const VertexBufferElement& element = elements[i];
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
            offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
        }
    }

    inline void Bind() const
    {
        glBindVertexArray(m_RendererID);
    }
    inline void UnBind() const
    {
        glBindVertexArray(0);
    }

private:
    unsigned int m_RendererID;
};

