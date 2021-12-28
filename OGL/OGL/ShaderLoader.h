#pragma once

// Library Includes
#include "NumptyBehavior.h"

class ShaderLoader
{
	
public:	
	static GLuint CreateProgram(const char* VertexShaderFilename, const char* FragmentShaderFilename);
	static GLuint CreateComputeProgram(const char* ComputeShaderFilename);
	static GLuint CreateGeometryProgram(const char* VertexShaderFilename, const char* FragmentShaderFilename, const char* GeometryShaderFileName);
private:
	ShaderLoader(void);
	~ShaderLoader(void);
	static GLuint CreateShader(GLenum shaderType, const char* shaderName);
	static std::string ReadShaderFile(const char *filename);
	static void PrintErrorDetails(bool isShader, GLuint id, const char* name);
};
