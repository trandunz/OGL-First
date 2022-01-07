#pragma once
#include "NumptyBehavior.h"

class IndexBuffer :
    public NumptyBehavior
{
public:
    IndexBuffer(const unsigned int* data, unsigned int indexCount)
        : m_IndexCount(indexCount)
    {

        // Generate Buffer
        glGenBuffers(1, &m_RendererID);

        // Bind the VBO specifying it's a GL_ARRAY_BUFFER
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);

        // Introduce the vertices into the VBO
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), data, GL_DYNAMIC_DRAW);
    }
    ~IndexBuffer()
    {
        glDeleteBuffers(1, &m_RendererID);
    }

    void Bind() const
    {
        // Bind the VBO specifying it's a GL_ARRAY_BUFFER
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }
    void UnBind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    unsigned int GetCount() const { return m_IndexCount; }

private:
    unsigned int m_RendererID = 0;
    unsigned int m_IndexCount = 0;
};