#pragma once
#include "NumptyBehavior.h"

class VertexBuffer :
    public NumptyBehavior
{
public:
    VertexBuffer() = default;
    VertexBuffer(const void* data, unsigned int size)
    {
        glCreateBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }
    VertexBuffer(std::vector<glm::mat4>& vecMat4, unsigned int instanceCount = 1)
    {
        glCreateBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, instanceCount * sizeof(glm::mat4), &vecMat4[0], GL_STATIC_DRAW);
    }
    VertexBuffer(std::vector<int>& vecint, unsigned int instanceCount = 1)
    {
        glCreateBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, instanceCount * sizeof(int), &vecint[0], GL_STATIC_DRAW);
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

