#pragma once

#include <sstream>

#include "NumptyBehavior.h"
#include "CShaderLoader.h"

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader : public NumptyBehavior
{
public:
    Shader(const std::string& _vertShader, const std::string& _geoShader, const std::string& _fragShader)
        : m_RendererID(0)
    {
        m_RendererID = CShaderLoader::CreateShader(_vertShader, _geoShader, _fragShader);
    }
    ~Shader()
    {
        glDeleteProgram(m_RendererID);
    }

    void Bind() const
    {
        glUseProgram(m_RendererID);
    }
    void UnBind() const
    {
        glUseProgram(0);
    }

    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
    {
        GLint location = GetUniformLocation(name);
        glUniform4f(location, v0, v1, v2, v3);
    }

    void SetUniform3f(const std::string& name, float v0, float v1, float v2)
    {
        GLint location = GetUniformLocation(name);
        glUniform3f(location, v0, v1, v2);
    }

    void SetUniformVec3f(const std::string& name, glm::vec3& vector3)
    {
        GLint location = GetUniformLocation(name);
        glUniform3f(location, vector3.x, vector3.y, vector3.z);
    }

    void SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
    {
        GLint location = GetUniformLocation(name);
        glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
    }

    void SetUniform1f(const std::string& name, float v0)
    {
        GLint location = GetUniformLocation(name);
        glUniform1f(location, v0);
    }

    void SetUniform1i(const std::string& name, int v0)
    {
        GLint location = GetUniformLocation(name);
        glUniform1i(location, v0);
    }

    void SetUniform1iv(const std::string& name,GLsizei size, GLint v0)
    {
        GLint location = GetUniformLocation(name);
        glUniform1iv(location, size, &v0);
    }

    void SetUniform3fv(const std::string& name, GLsizei size, float* v0)
    {
        GLint location = GetUniformLocation(name);
        glUniform3fv(location, size, v0);
    }

    void SetUniformBool(const std::string& name, int v0)
    {
        GLint location = GetUniformLocation(name);
        glUniform1i(location, v0);
    }

    ShaderProgramSource ParseShader(const std::string& filepath)
    {
        std::ifstream stream(filepath);

        enum class ShaderType
        {
            NONE = -1, 
            VERTEX = 0,
            FRAGMENT = 1
        };

        std::string line;
        std::stringstream ss[2];
        ShaderType Type = ShaderType::NONE;
        while (std::getline(stream, line))
        {
            if (line.find("#shader") != std::string::npos)
            {
                if (line.find("#vertex") != std::string::npos)
                    Type = ShaderType::VERTEX;
                else if (line.find("#fragment") != std::string::npos)
                    Type = ShaderType::FRAGMENT;
            }
            else
            {
                ss[(int)Type] << line << '\n';
            }
        }
        return { ss[0].str(), ss[1].str() };
    }
private:
    GLint GetUniformLocation(const std::string& name) const
    {
        if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
            return m_UniformLocationCache[name];

        else
        {
            int location = glGetUniformLocation(m_RendererID, name.c_str());
            m_UniformLocationCache[name] = location;
            return location;
        }
    }

    unsigned int m_RendererID;
    std::string m_FilePath;
    mutable std::unordered_map<std::string, GLint> m_UniformLocationCache;
};

