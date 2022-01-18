#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <GLM/gtc/quaternion.hpp>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <unordered_map>

struct STransform 
{
	glm::vec3 position{0,0,0};
	glm::vec3 rotation{ 0,0,0 };
	glm::vec3 scale{ 1.0f,1.0f,1.0f };
	float rotation_amount = 0.0f;
};

struct sTriangle
{
	float minX()
	{
		float minX = FLT_MAX;
		if (vertOne.x < minX)
		{
			minX = vertOne.x;
		}
		if (vertTwo.x < minX)
		{
			minX = vertTwo.x;
		}
		if (vertThree.x < minX)
		{
			minX = vertThree.x;
		}
		return minX;
	}
	float maxX()
	{
		float maxX = 0;
		if (vertOne.x > maxX)
		{
			maxX = vertOne.x;
		}
		if (vertTwo.x > maxX)
		{
			maxX = vertTwo.x;
		}
		if (vertThree.x > maxX)
		{
			maxX = vertThree.x;
		}
		return maxX;
	}
	float minY()
	{
		float minY = FLT_MAX;
		if (vertOne.y < minY)
		{
			minY = vertOne.y;
		}
		if (vertTwo.y < minY)
		{
			minY = vertTwo.y;
		}
		if (vertThree.y < minY)
		{
			minY = vertThree.y;
		}
		return minY;
	}
	float maxY()
	{
		float maxY = 0;
		if (vertOne.y > maxY)
		{
			maxY = vertOne.y;
		}
		if (vertTwo.y > maxY)
		{
			maxY = vertTwo.y;
		}
		if (vertThree.y > maxY)
		{
			maxY = vertThree.y;
		}
		return maxY;
	}
	float minZ()
	{
		float minZ = FLT_MAX;
		if (vertOne.z < minZ)
		{
			minZ = vertOne.z;
		}
		if (vertTwo.z < minZ)
		{
			minZ = vertTwo.z;
		}
		if (vertThree.z < minZ)
		{
			minZ = vertThree.z;
		}
		return minZ;
	}
	float maxZ()
	{
		float maxZ = 0;
		if (vertOne.z > maxZ)
		{
			maxZ = vertOne.z;
		}
		if (vertTwo.z > maxZ)
		{
			maxZ = vertTwo.z;
		}
		if (vertThree.z > maxZ)
		{
			maxZ = vertThree.z;
		}
		return maxZ;
	}


	glm::vec3 vertOne{ 0,0,0 };
	glm::vec3 vertTwo{ 0,0,0 };
	glm::vec3 vertThree{ 0,0,0 };
};

struct sSqaure
{
	float minX() 
	{ 
		float minX = triOne.minX() < triTwo.minX() ? triOne.minX() : triTwo.minX();
		return minX;
	}
	float maxX()
	{
		float maxX = triOne.maxX() < triTwo.maxX() ? triTwo.maxX() : triOne.maxX();
		return maxX;
	}
	float minY()
	{
		float minY = triOne.minY() < triTwo.minY() ? triOne.minY() : triTwo.minY();
		return minY;
	}
	float maxY()
	{
		float maxY = triOne.maxY() < triTwo.maxY() ? triTwo.maxY() : triOne.maxY();
		return maxY;
	}
	float minZ()
	{
		float minZ = triOne.minZ() < triTwo.minZ() ? triOne.minZ() : triTwo.minZ();
		return minZ;
	}
	float maxZ()
	{
		float maxZ = triOne.maxZ() < triTwo.maxZ() ? triTwo.maxZ() : triOne.maxZ();
		return maxZ;
	}

	sTriangle triOne;
	sTriangle triTwo;
};

struct sCube
{
	float minX()
	{
		float minX = 0.0f;
		minX = sqaureOne.minX() < sqaureTwo.minX() ? sqaureOne.minX() : sqaureTwo.minX();
		if (minX > sqaureThree.minX())
			minX = sqaureThree.minX();
		if (minX > sqaureFour.minX())
			minX = sqaureFour.minX();
		if (minX > sqaureFive.minX())
			minX = sqaureFive.minX();
		if (minX > sqaureSix.minX())
			minX = sqaureSix.minX();
		return minX;
	}
	float maxX()
	{
		float maxX = 0.0f;
		maxX = sqaureOne.maxX() < sqaureTwo.maxX() ? sqaureTwo.maxX() : sqaureOne.maxX();
		if (maxX < sqaureThree.maxX())
			maxX = sqaureThree.maxX();
		if (maxX < sqaureFour.maxX())
			maxX = sqaureFour.maxX();
		if (maxX < sqaureFive.maxX())
			maxX = sqaureFive.maxX();
		if (maxX < sqaureSix.maxX())
			maxX = sqaureSix.maxX();
		return maxX;
	}
	float minY()
	{
		float minY = 0.0f;
		minY = sqaureOne.minY() < sqaureTwo.minY() ? sqaureOne.minY() : sqaureTwo.minY();
		if (minY > sqaureThree.minY())
			minY = sqaureThree.minY();
		if (minY > sqaureFour.minY())
			minY = sqaureFour.minY();
		if (minY > sqaureFive.minY())
			minY = sqaureFive.minY();
		if (minY > sqaureSix.minY())
			minY = sqaureSix.minY();
		return minY;
	}
	float maxY()
	{
		float maxY = 0.0f;
		maxY = sqaureOne.maxY() < sqaureTwo.maxY() ? sqaureTwo.maxY() : sqaureOne.maxY();
		if (maxY < sqaureThree.maxY())
			maxY = sqaureThree.maxY();
		if (maxY < sqaureFour.maxY())
			maxY = sqaureFour.maxY();
		if (maxY < sqaureFive.maxY())
			maxY = sqaureFive.maxY();
		if (maxY < sqaureSix.maxY())
			maxY = sqaureSix.maxY();
		return maxY;
	}
	float minZ()
	{
		float minZ = 0.0f;
		minZ = sqaureOne.minZ() < sqaureTwo.minZ() ? sqaureOne.minZ() : sqaureTwo.minZ();
		if (minZ > sqaureThree.minZ())
			minZ = sqaureThree.minZ();
		if (minZ > sqaureFour.minZ())
			minZ = sqaureFour.minZ();
		if (minZ > sqaureFive.minZ())
			minZ = sqaureFive.minZ();
		if (minZ > sqaureSix.minZ())
			minZ = sqaureSix.minZ();
		return minZ;
	}
	float maxZ()
	{
		float maxZ = 0.0f;
		maxZ = sqaureOne.maxZ() < sqaureTwo.maxZ() ? sqaureTwo.maxZ() : sqaureOne.maxZ();
		if (maxZ < sqaureThree.maxZ())
			maxZ = sqaureThree.maxZ();
		if (maxZ < sqaureFour.maxZ())
			maxZ = sqaureFour.maxZ();
		if (maxZ < sqaureFive.maxZ())
			maxZ = sqaureFive.maxZ();
		if (maxZ < sqaureSix.maxZ())
			maxZ = sqaureSix.maxZ();
		return maxZ;
	}

	sSqaure sqaureOne;
	sSqaure sqaureTwo;

	sSqaure sqaureThree;
	sSqaure sqaureFour;

	sSqaure sqaureFive;
	sSqaure sqaureSix;
};

class NumptyBehavior
{
public:
	template <class T>
	static inline void CleanupPointer(T* _pointer)
	{
		DeletePointer(_pointer);
		_pointer = nullptr;
	}

protected:
	template <class T>
	static inline void DeletePointer(T* _pointer)
	{
		if (_pointer != nullptr)
		{
			delete _pointer;
		}
	}
};



