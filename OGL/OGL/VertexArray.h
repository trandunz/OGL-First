#pragma once
#include "NumptyBehavior.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
class VertexArray : public NumptyBehavior
{
public:
    VertexArray()
    {
        glCreateVertexArrays(1, &m_RendererID);
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
            glVertexAttribPointer(i, element.Count, element.Type, element.Normalized, layout.GetStride(), (const void*)offset);
            offset += element.Count * VertexBufferElement::GetSizeOfType(element.Type);
        }
        vb.UnBind();
    }
    inline void LinkAttibute(const VertexBuffer& vb, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
    {
        vb.Bind();
        glEnableVertexAttribArray(layout);
        glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
        vb.UnBind();
    }
    inline void StreamAttibute(const VertexBuffer& vb, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset, std::vector<glm::mat4>& _data ,unsigned int instanceCount = 1 )
    {
        vb.Bind();
        glBufferData(GL_ARRAY_BUFFER, instanceCount * sizeof(glm::mat4), &_data[0], GL_STREAM_DRAW);
        glEnableVertexAttribArray(layout);
        glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
        vb.UnBind();
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
    unsigned int m_RendererID = 0;
};

