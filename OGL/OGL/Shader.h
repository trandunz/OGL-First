#pragma once

#include <sstream>

#include "NumptyBehavior.h"
#include "CShaderLoader.h"

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader :
    public NumptyBehavior
{
public:
    Shader(const std::string& _vertShader, const std::string& _fragShader)
        : m_RendererID(0)
    {
       /* ShaderProgramSource source = ParseShader(filepath);*/
        //m_RendererID = CShaderLoader::CreateShader("Resources/Shaders/TriangleShader.vs", "Resources/Shaders/TriangleShader.fs");
        m_RendererID = CShaderLoader::CreateShader(_vertShader, _fragShader);
    }
    ~Shader()
    {
        glDeleteProgram(m_RendererID);
    }

    void CompileShader()
    {

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
        ShaderType type = ShaderType::NONE;
        while (std::getline(stream, line))
        {
            if (line.find("#shader") != std::string::npos)
            {
                if (line.find("#vertex") != std::string::npos)
                    type = ShaderType::VERTEX;
                else if (line.find("#fragment") != std::string::npos)
                    type = ShaderType::FRAGMENT;
            }
            else
            {
                ss[(int)type] << line << '\n';
            }
        }
        return { ss[0].str(), ss[1].str() };
    }
private:
    int GetUniformLocation(const std::string& name)
    {
        int location = glGetUniformLocation(m_RendererID, name.c_str());
        if (location == -1)
        {
            std::cout << "Warning: Uniform '" << name << "' Doesent Exist!" << std::endl;
        }
        return location;
    }

    unsigned int m_RendererID;
    std::string m_FilePath;
};

