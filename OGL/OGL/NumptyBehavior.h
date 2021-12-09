#pragma once

#include <iostream>
#include <GLFW/glfw3.h>

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

	struct Vector3
	{
		double x = 0.0;
		double y = 0.0;
		double z = 0.0;
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

