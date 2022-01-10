#pragma once
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>
#include <type_traits>
#include <new>
#include <string>
#include <vector>

#include "CShape.h"

template <typename T>
static std::vector<std::shared_ptr<T>> m_Components;

class GameObject
{
public:
	template <typename T, typename std::enable_if<std::is_base_of<GameObject, T>::value>::type* = nullptr>
	 T * GetComponent()
	{
		for (int i = 0; i < m_Components.size(); i++)
		{
			if (static_cast<T*>(m_Components[i].get()))
			{
				return static_cast<T*>(m_Components[i].get());
			}
		}

		return nullptr;
	}

	template <typename T, typename std::enable_if<std::is_base_of<GameObject, T>::value > ::type* = nullptr >
	 T* GetComponentInChildren(int _maxDepth = 1)
	{
		if (_maxDepth == 0)
			return nullptr;
		std::shared_ptr<T> val = GetComponent < T>();
		if (val)
			return val;
		for (int i = 0; i < m_Children.size(); i++)
		{
			val = m_Children[i]->GetComponentInChildren<T>(_maxDepth - 1);
			if (val)
				return val;
		}

		return nullptr;
	}

	template <typename T, typename std::enable_if<std::is_base_of<GameObject, T>::value > ::type* = nullptr >
	std::shared_ptr<T> AddComponent()
	{
		if (!GetComponent<T>())
		{
			std::shared_ptr<T> newComponent(new T(this));
			m_Components.push_back(newComponent);
			return newComponent;
		}
		else
		{
			std::cout << "ERROR : gameobject already has Component of type: " << typeid(T).name() << std::endl;
		}
	}

protected:
	std::vector<GameObject> m_Children;
};