#pragma once
#include "NumptyBehavior.h"

class CShaderLoader : public NumptyBehavior
{
public:
    inline static GLuint CreateShaderProgram(std::string _vertexShader, std::string _fragmentShader)
    {
        GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

        // Read shaders

        std::string vertShaderStr = readFile(_vertexShader);
        std::string fragShaderStr = readFile(_fragmentShader);
        const char* vertShaderSrc = vertShaderStr.c_str();
        const char* fragShaderSrc = fragShaderStr.c_str();

        GLint result = GL_FALSE;
        int logLength;

        // Compile vertex shader

        std::cout << "Compiling vertex shader." << std::endl;
        glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
        glCompileShader(vertShader);

        // Check vertex shader

        glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
        glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> vertShaderError((logLength > 1) ? logLength : 1);
        glGetShaderInfoLog(vertShader, logLength, NULL, &vertShaderError[0]);
        std::cout << &vertShaderError[0] << std::endl;

        // Compile fragment shader

        std::cout << "Compiling fragment shader." << std::endl;
        glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
        glCompileShader(fragShader);

        // Check fragment shader

        glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
        glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> fragShaderError((logLength > 1) ? logLength : 1);
        glGetShaderInfoLog(fragShader, logLength, NULL, &fragShaderError[0]);
        std::cout << &fragShaderError[0] << std::endl;

        std::cout << "Linking program" << std::endl;
        GLuint program = glCreateProgram();
        glAttachShader(program, vertShader);
        glAttachShader(program, fragShader);
        glLinkProgram(program);

        glGetProgramiv(program, GL_LINK_STATUS, &result);
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> programError((logLength > 1) ? logLength : 1);
        glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
        std::cout << &programError[0] << std::endl;

        glDeleteShader(vertShader);
        glDeleteShader(fragShader);

        return program;
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

