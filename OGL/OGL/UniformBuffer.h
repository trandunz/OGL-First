#pragma once
#include "NumptyBehavior.h"
class UniformBuffer : public NumptyBehavior
{
public:
    UniformBuffer(const void* data, unsigned int size)
    {
        glCreateBuffers(1, &m_RendererID);
        glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID);
        glBufferData(GL_UNIFORM_BUFFER, size, data, GL_STATIC_DRAW);
        glBindBufferRange(GL_UNIFORM_BUFFER, 0, m_RendererID, 0, size);
    }
    UniformBuffer(std::vector<glm::mat4>& vecMat4, unsigned int instanceCount = 1)
    {
        glCreateBuffers(1, &m_RendererID);
        glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID);
        glBufferData(GL_UNIFORM_BUFFER, instanceCount * sizeof(glm::mat4), &vecMat4[0], GL_STATIC_DRAW);
        glBindBufferRange(GL_UNIFORM_BUFFER, 0, m_RendererID, 0, instanceCount * sizeof(glm::mat4));
    }

    ~UniformBuffer()
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
    unsigned int m_RendererID;
};

