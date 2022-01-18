#pragma once
#include "NumptyBehavior.h"

class VertexBuffer :
    public NumptyBehavior
{
public:
    VertexBuffer(const void* data, unsigned int size)
    {
        glCreateBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }
    ~VertexBuffer()
    {
        UnBind();
        glDeleteBuffers(1, &m_RendererID);
    }

    void Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }
    void UnBind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

private:
    unsigned int m_RendererID = 0;
};

