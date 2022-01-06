#pragma once
#include "NumptyBehavior.h"

class CShaderLoader : public NumptyBehavior
{
public:
    static const bool m_bDebug = false;

    inline static GLuint CompileVertShader(std::string _source)
    {
        // Creation
        GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
        const char* src = _source.c_str();
        glShaderSource(vertShader, 1, &src, nullptr);

        // Compile vertex shader
        if (m_bDebug)
        {
            std::cout << "Compiling vertex shader." << std::endl;
        }
        glCompileShader(vertShader);

        // Debug
        int result;
        glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE)
        {
            int length;
            glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &length);
            char* message = (char*)_malloca(length * sizeof(char));
            glGetShaderInfoLog(vertShader, length, &length, message);
            std::cout << "Failed to Compile Vertex Shader" << std::endl;
            std::cout << message << std::endl;
            glDeleteShader(vertShader);
            return 0;
        }

        return vertShader;
    }

    inline static GLuint CompileFragShader(std::string _source)
    {
        GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
        const char* src = _source.c_str();
        glShaderSource(fragShader, 1, &src, nullptr);

        // Compile Frag shader
        if (m_bDebug)
        {
            std::cout << "Compiling fragment shader." << std::endl;
        }
        glCompileShader(fragShader);

        // Debug
        int result;
        glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE)
        {
            int length;
            glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &length);
            char* message = (char*)_malloca(length * sizeof(char));
            glGetShaderInfoLog(fragShader, length, &length, message);
            std::cout << "Failed to Compile Vertex Shader" << std::endl;
            std::cout << message << std::endl;
            glDeleteShader(fragShader);
            return 0;
        }

        return fragShader;
    }

    inline static GLuint CreateShader(std::string _vertexShader, std::string _fragmentShader)
    {
        // Program
        GLuint program = glCreateProgram();

        // Shaders
        GLuint vertShader = CompileVertShader(readFile(_vertexShader));
        GLuint fragShader = CompileFragShader(readFile(_fragmentShader));

        if (m_bDebug)
        {
            std::cout << "Attaching Shaders" << std::endl;
        }
        glAttachShader(program, vertShader);
        glAttachShader(program, fragShader);

        if (m_bDebug)
        {
            std::cout << "Linking program" << std::endl;
        }
        glLinkProgram(program);
        glValidateProgram(program);

        if (m_bDebug)
        {
            std::cout << "Deleting Shaders" << std::endl;
        }
        glDeleteShader(vertShader);
        glDeleteShader(fragShader);

        return program;

        //GLint result = GL_FALSE;
        //int logLength;

        //// Check vertex shader
        //glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
        //glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLength);
        //std::vector<char> vertShaderError((logLength > 1) ? logLength : 1);
        //glGetShaderInfoLog(vertShader, logLength, NULL, &vertShaderError[0]);
        //if (m_bDebug)
        //{
        //    std::cout << &vertShaderError[0] << std::endl;
        //}

        //// Check fragment shader
        //glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
        //glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLength);
        //std::vector<char> fragShaderError((logLength > 1) ? logLength : 1);
        //glGetShaderInfoLog(fragShader, logLength, NULL, &fragShaderError[0]);
        //if (m_bDebug)
        //{
        //    std::cout << &fragShaderError[0] << std::endl;
        //}

        //glGetProgramiv(program, GL_LINK_STATUS, &result);
        //glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
        //std::vector<char> programError((logLength > 1) ? logLength : 1);
        //glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
        //if (m_bDebug)
        //{
        //    std::cout << &programError[0] << std::endl;
        //}

        //return program;
    }

    inline static std::string readFile(std::string _fileAddress)
    {
        std::string content;
        std::ifstream fileStream(_fileAddress, std::ios::in);

        if (!fileStream.is_open()) {
            std::cerr << "Could not read file " << _fileAddress << ". File does not exist." << std::endl;
            return "";
        }

        std::string line = "";
        while (!fileStream.eof()) {
            std::getline(fileStream, line);
            content.append(line + "\n");
        }

        fileStream.close();
        return content;
    }

};

