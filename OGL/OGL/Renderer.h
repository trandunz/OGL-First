#pragma once
#include "NumptyBehavior.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

struct Material
{
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};

struct DirLight
{
    glm::vec3 direction = {-0.2f, -1.0f, -0.3f};

    glm::vec3 ambient = { 0.05f, 0.05f, 0.05f };
    glm::vec3 diffuse = { 0.4f, 0.4f, 0.4f };
    glm::vec3 specular = { 0.5f, 0.5f, 0.5f };
};

struct PointLight
{
    glm::vec3 position;

    float constant;
    float linear;
    float quadratic;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

struct SpotLight
{
    glm::vec3 position;
    glm::vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

class Renderer : public NumptyBehavior
{
public:
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, GLsizei instancecount = 1) const
	{
		shader.Bind();
		va.Bind();
		if (&ib != nullptr)
		{
			ib.Bind();
			if (instancecount > 1)
				glDrawElementsInstanced(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0, instancecount);
			else
				glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
		}
		else
		{
            if (instancecount > 1)
                glDrawArraysInstanced(GL_TRIANGLES,0, 36, instancecount);
			else
                glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}
};

