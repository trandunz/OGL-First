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
        // Generate Buffers
        glGenVertexArrays(1, &m_RendererID);

        // Make the VAO the current Vertex Array Object by binding it
        glBindVertexArray(m_RendererID);

        // Enable the Vertex Attribute so that OpenGL knows to use it // attribPointer is that of the laast param above
        glEnableVertexAttribArray(0);

        // Configure the Vertex Attribute so that OpenGL knows how to read the VBO
        // 0, 3 dimentions, type is float, dont normialize it, stride between each vertex is 3 times float, offset for the vertex types, we nly have positition in our array so we will start at bite 0.
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);
    }
    ~VertexArray()
    {
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

            // Enable the Vertex Attribute so that OpenGL knows to use it // attribPointer is that of the laast param above
            glEnableVertexAttribArray(i);

            // Configure the Vertex Attribute so that OpenGL knows how to read the VBO
            // 0, 3 dimentions, type is float, dont normialize it, stride between each vertex is 3 times float, offset for the vertex types, we nly have positition in our array so we will start at bite 0.
            glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
            offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
        }
    }

    inline void Bind() const
    {
        // Make the VAO the current Vertex Array Object by binding it
        glBindVertexArray(m_RendererID);
    }
    inline void UnBind() const
    {
        glBindVertexArray(0);
    }

private:
    unsigned int m_RendererID;
};

