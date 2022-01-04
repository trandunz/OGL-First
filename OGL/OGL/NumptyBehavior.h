#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
//#include <ImGui/imgui.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

class Vector3
{
public:
	inline Vector3& operator += (const Vector3& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this; // return the result by reference
	}

	inline Vector3& operator *= (const Vector3& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		return *this; // return the result by reference
	}

	inline bool operator == (const Vector3& rhs)
	{
		bool truthValue = false;
		if (x == rhs.x && y == rhs.y && z == rhs.z)
		{
			truthValue = true;
		}
		return truthValue;
	}

	inline friend Vector3 operator + (Vector3 lhs, const Vector3& rhs)
	{
		lhs += rhs;
		return lhs; // return the result by value (uses move constructor)
	}

	inline void setPosition(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	double x = 0.0;
	double y = 0.0;
	double z = 0.0;
};

class NumptyBehavior
{
public:
	struct Vector4
	{
		double x = 0.0;
		double y = 0.0;
		double z = 0.0;
		double w = 0.0;
	};

	struct Vector2
	{
		double x = 0.0;
		double y = 0.0;
	};

	template <class T>
	static inline void CleanupPointer(T* _pointer)
	{
		DeletePointer(_pointer);
		_pointer = nullptr;
	}

	inline Vector3 CalculateChangeInPos(Vector3 _posOne, Vector3 _posTwo)
	{
		Vector3 dS;
		dS.x = _posOne.x - _posTwo.x;
		dS.y = _posOne.y - _posTwo.y;
		dS.z = _posOne.z - _posTwo.z;
		return dS;
	}

	inline Vector3 CalculateVelocity(Vector3 _ds, float _dt)
	{
		_ds.x /= _dt;
		_ds.y /= _dt;
		_ds.z /= _dt;
		return _ds;
	}

	inline Vector3 CalculateMomentum(Vector3 _ds, float _dt, float _mass)
	{
		Vector3 velocity = CalculateVelocity(_ds, _dt);
		_ds.x = velocity.x * _mass;
		_ds.y = velocity.y * _mass;
		_ds.z = velocity.z * _mass;
	}

	inline Vector3 CalculateMomentum(Vector3 _velocity, float _mass)
	{
		_velocity.x *= _mass;
		_velocity.y *= _mass;
		_velocity.z *= _mass;
		return _velocity;
	}

	inline Vector3 CalculateChangeInMomentum(Vector3 _velocityOne, float _massOne, Vector3 _velocityTwo, float _massTwo)
	{
		Vector3 dP;
		dP.x = (_velocityOne.x * _massOne) - (_velocityTwo.x * _massTwo);
		dP.y = (_velocityOne.y * _massOne) - (_velocityTwo.y * _massTwo);
		dP.z = (_velocityOne.x * _massOne) - (_velocityTwo.x * _massTwo);
		return dP;
	}

	inline int DotProduct(Vector3 _vecOne, Vector3 _vecTwo)
	{
		int product = 0;

		// Loop for calculate cot product
		product = product + _vecOne.x * _vecTwo.x;
		product = product + _vecOne.y * _vecTwo.y;
		product = product + _vecOne.z * _vecTwo.z;
			
		return product;
	}

	inline Vector3 CrossProduct(Vector3 _vecOne, Vector3 _vecTwo)
	{
		Vector3 crossProduct;
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



