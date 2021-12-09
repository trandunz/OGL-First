#pragma once

#include <iostream>
#include <GLFW/glfw3.h>

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

