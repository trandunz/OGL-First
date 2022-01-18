#pragma once
#include "NumptyBehavior.h"
class Physics : public NumptyBehavior
{
public:
	static void TestCubeCollision(STransform _transform, glm::vec3 _point = glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX))
	{
		sCube testCube;

		// Make a Cube
		{
			testCube.sqaureOne.triOne.vertOne.x = -0.5f;
			testCube.sqaureOne.triOne.vertOne.y = -0.5f;
			testCube.sqaureOne.triOne.vertOne.z = -0.5f;

			testCube.sqaureOne.triOne.vertTwo.x = 0.5f;
			testCube.sqaureOne.triOne.vertTwo.y = -0.5f;
			testCube.sqaureOne.triOne.vertTwo.z = -0.5f;

			testCube.sqaureOne.triOne.vertThree.x = 0.5f;
			testCube.sqaureOne.triOne.vertThree.y = 0.5f;
			testCube.sqaureOne.triOne.vertThree.z = -0.5f;
			//
			testCube.sqaureOne.triTwo.vertOne.x = 0.5f;
			testCube.sqaureOne.triTwo.vertOne.y = 0.5f;
			testCube.sqaureOne.triTwo.vertOne.z = -0.5f;

			testCube.sqaureOne.triTwo.vertTwo.x = -0.5f;
			testCube.sqaureOne.triTwo.vertTwo.y = 0.5f;
			testCube.sqaureOne.triTwo.vertTwo.z = -0.5f;

			testCube.sqaureOne.triTwo.vertThree.x = -0.5f;
			testCube.sqaureOne.triTwo.vertThree.y = -0.5f;
			testCube.sqaureOne.triTwo.vertThree.z = -0.5f;

			//
			//

			testCube.sqaureTwo.triOne.vertOne.x = -0.5f;
			testCube.sqaureTwo.triOne.vertOne.y = -0.5f;
			testCube.sqaureTwo.triOne.vertOne.z = 0.5f;

			testCube.sqaureTwo.triOne.vertTwo.x = 0.5f;
			testCube.sqaureTwo.triOne.vertTwo.y = -0.5f;
			testCube.sqaureTwo.triOne.vertTwo.z = 0.5f;

			testCube.sqaureTwo.triOne.vertThree.x = 0.5f;
			testCube.sqaureTwo.triOne.vertThree.y = 0.5f;
			testCube.sqaureTwo.triOne.vertThree.z = 0.5f;
			//
			testCube.sqaureTwo.triTwo.vertOne.x = 0.5f;
			testCube.sqaureTwo.triTwo.vertOne.y = 0.5f;
			testCube.sqaureTwo.triTwo.vertOne.z = 0.5f;

			testCube.sqaureTwo.triTwo.vertTwo.x = -0.5f;
			testCube.sqaureTwo.triTwo.vertTwo.y = 0.5f;
			testCube.sqaureTwo.triTwo.vertTwo.z = 0.5f;

			testCube.sqaureTwo.triTwo.vertThree.x = -0.5f;
			testCube.sqaureTwo.triTwo.vertThree.y = -0.5f;
			testCube.sqaureTwo.triTwo.vertThree.z = 0.5f;

			//
			//

			testCube.sqaureThree.triOne.vertOne.x = -0.5f;
			testCube.sqaureThree.triOne.vertOne.y = 0.5f;
			testCube.sqaureThree.triOne.vertOne.z = 0.5f;

			testCube.sqaureThree.triOne.vertTwo.x = -0.5f;
			testCube.sqaureThree.triOne.vertTwo.y = 0.5f;
			testCube.sqaureThree.triOne.vertTwo.z = -0.5f;

			testCube.sqaureThree.triOne.vertThree.x = -0.5f;
			testCube.sqaureThree.triOne.vertThree.y = -0.5f;
			testCube.sqaureThree.triOne.vertThree.z = -0.5f;
			//
			testCube.sqaureThree.triTwo.vertOne.x = -0.5f;
			testCube.sqaureThree.triTwo.vertOne.y = -0.5f;
			testCube.sqaureThree.triTwo.vertOne.z = -0.5f;

			testCube.sqaureThree.triTwo.vertTwo.x = -0.5f;
			testCube.sqaureThree.triTwo.vertTwo.y = -0.5f;
			testCube.sqaureThree.triTwo.vertTwo.z = 0.5f;

			testCube.sqaureThree.triTwo.vertThree.x = -0.5f;
			testCube.sqaureThree.triTwo.vertThree.y = 0.5f;
			testCube.sqaureThree.triTwo.vertThree.z = 0.5f;

			//
			//

			testCube.sqaureFour.triOne.vertOne.x = 0.5f;
			testCube.sqaureFour.triOne.vertOne.y = 0.5f;
			testCube.sqaureFour.triOne.vertOne.z = 0.5f;

			testCube.sqaureFour.triOne.vertTwo.x = 0.5f;
			testCube.sqaureFour.triOne.vertTwo.y = 0.5f;
			testCube.sqaureFour.triOne.vertTwo.z = -0.5f;

			testCube.sqaureFour.triOne.vertThree.x = 0.5f;
			testCube.sqaureFour.triOne.vertThree.y = -0.5f;
			testCube.sqaureFour.triOne.vertThree.z = -0.5f;
			//
			testCube.sqaureFour.triTwo.vertOne.x = 0.5f;
			testCube.sqaureFour.triTwo.vertOne.y = -0.5f;
			testCube.sqaureFour.triTwo.vertOne.z = -0.5f;

			testCube.sqaureFour.triTwo.vertTwo.x = 0.5f;
			testCube.sqaureFour.triTwo.vertTwo.y = -0.5f;
			testCube.sqaureFour.triTwo.vertTwo.z = 0.5f;

			testCube.sqaureFour.triTwo.vertThree.x = 0.5f;
			testCube.sqaureFour.triTwo.vertThree.y = 0.5f;
			testCube.sqaureFour.triTwo.vertThree.z = 0.5f;

			//
			//

			testCube.sqaureFive.triOne.vertOne.x = -0.5f;
			testCube.sqaureFive.triOne.vertOne.y = -0.5f;
			testCube.sqaureFive.triOne.vertOne.z = -0.5f;

			testCube.sqaureFive.triOne.vertTwo.x = 0.5f;
			testCube.sqaureFive.triOne.vertTwo.y = -0.5f;
			testCube.sqaureFive.triOne.vertTwo.z = -0.5f;

			testCube.sqaureFive.triOne.vertThree.x = 0.5f;
			testCube.sqaureFive.triOne.vertThree.y = -0.5f;
			testCube.sqaureFive.triOne.vertThree.z = 0.5f;
			//
			testCube.sqaureFive.triTwo.vertOne.x = 0.5f;
			testCube.sqaureFive.triTwo.vertOne.y = -0.5f;
			testCube.sqaureFive.triTwo.vertOne.z = 0.5f;

			testCube.sqaureFive.triTwo.vertTwo.x = -0.5f;
			testCube.sqaureFive.triTwo.vertTwo.y = -0.5f;
			testCube.sqaureFive.triTwo.vertTwo.z = 0.5f;

			testCube.sqaureFive.triTwo.vertThree.x = -0.5f;
			testCube.sqaureFive.triTwo.vertThree.y = -0.5f;
			testCube.sqaureFive.triTwo.vertThree.z = -0.5f;

			//
			//

			testCube.sqaureSix.triOne.vertOne.x = -0.5f;
			testCube.sqaureSix.triOne.vertOne.y = 0.5f;
			testCube.sqaureSix.triOne.vertOne.z = -0.5f;

			testCube.sqaureSix.triOne.vertTwo.x = 0.5f;
			testCube.sqaureSix.triOne.vertTwo.y = 0.5f;
			testCube.sqaureSix.triOne.vertTwo.z = -0.5f;

			testCube.sqaureSix.triOne.vertThree.x = 0.5f;
			testCube.sqaureSix.triOne.vertThree.y = 0.5f;
			testCube.sqaureSix.triOne.vertThree.z = 0.5f;
			//
			testCube.sqaureSix.triTwo.vertOne.x = 0.5f;
			testCube.sqaureSix.triTwo.vertOne.y = 0.5f;
			testCube.sqaureSix.triTwo.vertOne.z = 0.5f;

			testCube.sqaureSix.triTwo.vertTwo.x = -0.5f;
			testCube.sqaureSix.triTwo.vertTwo.y = 0.5f;
			testCube.sqaureSix.triTwo.vertTwo.z = 0.5f;

			testCube.sqaureSix.triTwo.vertThree.x = -0.5f;
			testCube.sqaureSix.triTwo.vertThree.y = 0.5f;
			testCube.sqaureSix.triTwo.vertThree.z = -0.5f;
		}
		
		// Create Model Matrix Based On Transform
		glm::mat4 model = glm::translate(glm::mat4(1.0f), _transform.position);
		if (_transform.rotation.x != 0.0f)
		{
			model = glm::rotate(model, _transform.rotation.x, _transform.rotation);
		}
		if (_transform.rotation.y != 0.0f)
		{
			model = glm::rotate(model, _transform.rotation.y, _transform.rotation);
		}
		if (_transform.rotation.z != 0.0f)
		{
			model = glm::rotate(model, _transform.rotation.z, _transform.rotation);
		}
		model = glm::scale(model, _transform.scale);

		// Apply / Calculate its Transformation Matrix
		{
			testCube.sqaureOne.triOne.vertOne = glm::vec3(model * glm::vec4(testCube.sqaureOne.triOne.vertOne, 1.0));
			testCube.sqaureOne.triOne.vertTwo = glm::vec3(model * glm::vec4(testCube.sqaureOne.triOne.vertTwo, 1.0));
			testCube.sqaureOne.triTwo.vertOne = glm::vec3(model * glm::vec4(testCube.sqaureOne.triTwo.vertOne, 1.0));
			testCube.sqaureOne.triTwo.vertTwo = glm::vec3(model * glm::vec4(testCube.sqaureOne.triTwo.vertTwo, 1.0));

			testCube.sqaureTwo.triOne.vertOne = glm::vec3(model * glm::vec4(testCube.sqaureTwo.triOne.vertOne, 1.0));
			testCube.sqaureTwo.triOne.vertTwo = glm::vec3(model * glm::vec4(testCube.sqaureTwo.triOne.vertTwo, 1.0));
			testCube.sqaureTwo.triTwo.vertOne = glm::vec3(model * glm::vec4(testCube.sqaureTwo.triTwo.vertOne, 1.0));
			testCube.sqaureTwo.triTwo.vertTwo = glm::vec3(model * glm::vec4(testCube.sqaureTwo.triTwo.vertTwo, 1.0));

			testCube.sqaureThree.triOne.vertOne = glm::vec3(model * glm::vec4(testCube.sqaureThree.triOne.vertOne, 1.0));
			testCube.sqaureThree.triOne.vertTwo = glm::vec3(model * glm::vec4(testCube.sqaureThree.triOne.vertTwo, 1.0));
			testCube.sqaureThree.triTwo.vertOne = glm::vec3(model * glm::vec4(testCube.sqaureThree.triTwo.vertOne, 1.0));
			testCube.sqaureThree.triTwo.vertTwo = glm::vec3(model * glm::vec4(testCube.sqaureThree.triTwo.vertTwo, 1.0));

			testCube.sqaureFour.triOne.vertOne = glm::vec3(model * glm::vec4(testCube.sqaureFour.triOne.vertOne, 1.0));
			testCube.sqaureFour.triOne.vertTwo = glm::vec3(model * glm::vec4(testCube.sqaureFour.triOne.vertTwo, 1.0));
			testCube.sqaureFour.triTwo.vertOne = glm::vec3(model * glm::vec4(testCube.sqaureFour.triTwo.vertOne, 1.0));
			testCube.sqaureFour.triTwo.vertTwo = glm::vec3(model * glm::vec4(testCube.sqaureFour.triTwo.vertTwo, 1.0));

			testCube.sqaureFive.triOne.vertOne = glm::vec3(model * glm::vec4(testCube.sqaureFive.triOne.vertOne, 1.0));
			testCube.sqaureFive.triOne.vertTwo = glm::vec3(model * glm::vec4(testCube.sqaureFive.triOne.vertTwo, 1.0));
			testCube.sqaureFive.triTwo.vertOne = glm::vec3(model * glm::vec4(testCube.sqaureFive.triTwo.vertOne, 1.0));
			testCube.sqaureFive.triTwo.vertTwo = glm::vec3(model * glm::vec4(testCube.sqaureFive.triTwo.vertTwo, 1.0));

			testCube.sqaureSix.triOne.vertOne = glm::vec3(model * glm::vec4(testCube.sqaureSix.triOne.vertOne, 1.0));
			testCube.sqaureSix.triOne.vertTwo = glm::vec3(model * glm::vec4(testCube.sqaureSix.triOne.vertTwo, 1.0));
			testCube.sqaureSix.triTwo.vertOne = glm::vec3(model * glm::vec4(testCube.sqaureSix.triTwo.vertOne, 1.0));
			testCube.sqaureSix.triTwo.vertTwo = glm::vec3(model * glm::vec4(testCube.sqaureSix.triTwo.vertTwo, 1.0));
		}
		
		// Test For Its Collision
		if (_point == glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX))
			std::cout << IsPointInCube(testCube, glm::vec3(0.5, 0.5, 0.5)) << "= Test Collision Value" << std::endl;
		else
			std::cout << IsPointInCube(testCube, _point) << "= Test Collision Value" << std::endl;
	}

	static bool IsPointInCube(sCube _cube, glm::vec3 _point)
	{
		return (_point.x >= _cube.minX() && _point.x <= _cube.maxX()) &&
			(_point.y >= _cube.minY() && _point.y <= _cube.maxY()) &&
			(_point.z >= _cube.minZ() && _point.z <= _cube.maxZ());
	}

	static bool IsPointInSqaure(sSqaure _square, glm::vec2 _point)
	{
		return (IsPointInTri(_square.triOne, _point) || IsPointInTri(_square.triTwo, _point));
	}

	static bool IsPointInTri(sTriangle _triangle, glm::vec2 _point)
	{

		// get the area of the triangle
		float areaOrig = abs((_triangle.vertTwo.x - _triangle.vertOne.x) * (_triangle.vertThree.y - _triangle.vertOne.y) - (_triangle.vertThree.x - _triangle.vertOne.x) * (_triangle.vertTwo.y - _triangle.vertOne.y));

		// get the area of 3 triangles made between the point
		// and the corners of the triangle
		float area1 = abs((_triangle.vertOne.x - _point.x) * (_triangle.vertTwo.y - _point.y) - (_triangle.vertTwo.x - _point.x) * (_triangle.vertOne.y - _point.y));
		float area2 = abs((_triangle.vertTwo.x - _point.x) * (_triangle.vertThree.y - _point.y) - (_triangle.vertThree.x - _point.x) * (_triangle.vertTwo.y - _point.y));
		float area3 = abs((_triangle.vertThree.x - _point.x) * (_triangle.vertOne.y - _point.y) - (_triangle.vertOne.x - _point.x) * (_triangle.vertThree.y - _point.y));

		// if the sum of the three areas equals the original,
		// we're inside the triangle!
		if (area1 + area2 + area3 == areaOrig) 
		{
			return true;
		}
		return false;
	}
};

