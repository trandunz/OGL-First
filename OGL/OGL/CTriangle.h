#pragma once
#include "NumptyBehavior.h"

class CTriangle : public NumptyBehavior
{
public:
	CTriangle();
	virtual ~CTriangle();

	void Render();
	void Update(float _dt);

private:
	GLFWwindow* m_RenderWindow;

};

