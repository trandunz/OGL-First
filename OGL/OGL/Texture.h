#pragma once
#include "NumptyBehavior.h"

class Texture :
    public NumptyBehavior
{
public:
    Texture(const std::string& path);
    
    ~Texture()
    {
        glDeleteTextures(1, &m_RendererID);
    }

    void Bind(unsigned int slot = 0) const
    {
        glActiveTexture(GL_TEXTURE + slot);
        glBindBuffer(GL_TEXTURE_2D, m_RendererID);
    }

    void UnBind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    inline int GetWidth() { return m_Width; }
    inline int GetHeight() { return m_Height; }

private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;
};


