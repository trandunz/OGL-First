#pragma once
#include "NumptyBehavior.h"

class VertexBuffer :
    public NumptyBehavior
{
public:
    VertexBuffer(const void* data, unsigned int size)
    {
        // Generate Buffer
        glGenBuffers(1, &m_RendererID);

        // Bind the VBO specifying it's a GL_ARRAY_BUFFER
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

        // Introduce the vertices into the VBO
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
    }
    ~VertexBuffer()
    {
        UnBind();
        glDeleteBuffers(1, &m_RendererID);
    }

    void Bind() const
    {
        // Bind the VBO specifying it's a GL_ARRAY_BUFFER
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }
    void UnBind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

private:
    unsigned int m_RendererID = 0;
};

