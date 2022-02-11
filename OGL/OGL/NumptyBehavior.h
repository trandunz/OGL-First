#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
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



