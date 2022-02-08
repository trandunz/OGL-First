#pragma once
#include "GLM/vec3.hpp"
#include "GLM/vec4.hpp"
#include "GLM/mat4x4.hpp"
class Physics
{
	
public:
	struct Cube
	{
		glm::vec3 Points_pos[4]{ {-0.5f,-0.5f,0.5f},{0.5f,0.5f,0.5f},{-0.5f,0.5f,0.5f},{0.5f,-0.5f,0.5f} };
		glm::vec3 Points_neg[4]{ {-0.5f,-0.5f,-0.5f},{0.5f,0.5f,-0.5f},{-0.5f,0.5f,-0.5f},{0.5f,-0.5f,-0.5f} };
		glm::vec3 Get_Low_pos() { return ModelMat * glm::vec4(Points_pos[0], 1.0f); }
		glm::vec3 Get_High_pos() { return ModelMat * glm::vec4(Points_pos[1], 1.0f); }
		glm::vec3 Get_Low_neg() { return ModelMat * glm::vec4(Points_neg[0], 1.0f); }
		glm::vec3 Get_High_neg() { return ModelMat * glm::vec4(Points_neg[1], 1.0f); }
		glm::vec3 GetPos() { return ModelMat * glm::vec4(glm::vec3(), 1.0f); }

		glm::mat4 ModelMat = glm::mat4(1.0);
	};
	static bool Intersection(Cube& _cubeOne, Cube& _cubeTwo);
	static bool Point(Cube& _cubeOne, glm::vec3 _point);
};

