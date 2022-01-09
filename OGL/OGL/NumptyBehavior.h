#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <GLM/gtc/quaternion.hpp>
//#include <ImGui/imgui.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <unordered_map>

class NumptyBehavior
{
public:
	template <class T>
	static inline void CleanupPointer(T* _pointer)
	{
		DeletePointer(_pointer);
		_pointer = nullptr;
	}

	inline glm::vec3 CalculateChangeInPos(glm::vec3 _posOne, glm::vec3 _posTwo)
	{
		glm::vec3 dS;
		dS.x = _posOne.x - _posTwo.x;
		dS.y = _posOne.y - _posTwo.y;
		dS.z = _posOne.z - _posTwo.z;
		return dS;
	}

	inline glm::vec3 CalculateVelocity(glm::vec3 _ds, float _dt)
	{
		_ds.x /= _dt;
		_ds.y /= _dt;
		_ds.z /= _dt;
		return _ds;
	}

	inline glm::vec3 CalculateMomentum(glm::vec3 _ds, float _dt, float _mass)
	{
		glm::vec3 velocity = CalculateVelocity(_ds, _dt);
		_ds.x = velocity.x * _mass;
		_ds.y = velocity.y * _mass;
		_ds.z = velocity.z * _mass;
	}

	inline glm::vec3 CalculateMomentum(glm::vec3 _velocity, float _mass)
	{
		_velocity.x *= _mass;
		_velocity.y *= _mass;
		_velocity.z *= _mass;
		return _velocity;
	}

	inline glm::vec3 CalculateChangeInMomentum(glm::vec3 _velocityOne, float _massOne, glm::vec3 _velocityTwo, float _massTwo)
	{
		glm::vec3 dP;
		dP.x = (_velocityOne.x * _massOne) - (_velocityTwo.x * _massTwo);
		dP.y = (_velocityOne.y * _massOne) - (_velocityTwo.y * _massTwo);
		dP.z = (_velocityOne.x * _massOne) - (_velocityTwo.x * _massTwo);
		return dP;
	}

	inline int DotProduct(glm::vec3 _vecOne, glm::vec3 _vecTwo)
	{
		int product = 0;

		// Loop for calculate cot product
		product = product + _vecOne.x * _vecTwo.x;
		product = product + _vecOne.y * _vecTwo.y;
		product = product + _vecOne.z * _vecTwo.z;
			
		return product;
	}

	inline glm::vec3 CrossProduct(glm::vec3 _vecOne, glm::vec3 _vecTwo)
	{
		glm::vec3 crossProduct;
		crossProduct.x = _vecOne.y * _vecTwo.z - _vecOne.z * _vecTwo.y;
		crossProduct.y = _vecOne.z * _vecTwo.x - _vecOne.x * _vecTwo.z;
		crossProduct.z = _vecOne.x * _vecTwo.y - _vecOne.y * _vecTwo.x;
		return crossProduct;
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



