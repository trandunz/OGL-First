#pragma once

#ifndef PHYSICS_H
#define PHYSICS_H
#include "Includes.h"

namespace Harmony
{
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
        static bool hitsOBB(const glm::vec3& min, const glm::vec3& max, const glm::mat4 modelMatrix, const glm::vec3& origin, const glm::vec3& direction)
        {
            float scaleX = sqrt(modelMatrix[0].x * modelMatrix[0].x + modelMatrix[0].y * modelMatrix[0].y + modelMatrix[0].z * modelMatrix[0].z);
            float scaleY = sqrt(modelMatrix[1].x * modelMatrix[1].x + modelMatrix[1].y * modelMatrix[1].y + modelMatrix[1].z * modelMatrix[1].z);
            float scaleZ = sqrt(modelMatrix[2].x * modelMatrix[2].x + modelMatrix[2].y * modelMatrix[2].y + modelMatrix[2].z * modelMatrix[2].z);
            glm::scale(modelMatrix, glm::vec3(scaleX, scaleY, scaleZ));

            float tMin = 0.0f;
            float tMax = 100000.0f;
            glm::vec3 OBBposition_worldspace(modelMatrix[3].x, modelMatrix[3].y, modelMatrix[3].z);
            glm::vec3 delta = OBBposition_worldspace - origin;

            {
                glm::vec3 xaxis(modelMatrix[0].x, modelMatrix[0].y, modelMatrix[0].z);
                float e = glm::dot(xaxis, delta);
                float f = glm::dot(direction, xaxis);

                if (fabs(f) > 0.001f) {
                    float t1 = (e + min.x) / f;
                    float t2 = (e + max.x) / f;

                    if (t1 > t2) std::swap(t1, t2);

                    if (t2 < tMax) tMax = t2;
                    if (t1 > tMin) tMin = t1;
                    if (tMin > tMax) return {false};

                }
                else {
                    if (-e + min.x > 0.0f || -e + max.x < 0.0f) return { false };
                }
            }


            {
                glm::vec3 yaxis(modelMatrix[1].x, modelMatrix[1].y, modelMatrix[1].z);
                float e = glm::dot(yaxis, delta);
                float f = glm::dot(direction, yaxis);

                if (fabs(f) > 0.001f) {

                    float t1 = (e + min.y) / f;
                    float t2 = (e + max.y) / f;

                    if (t1 > t2) std::swap(t1, t2);

                    if (t2 < tMax) tMax = t2;
                    if (t1 > tMin) tMin = t1;
                    if (tMin > tMax) return { false };

                }
                else {
                    if (-e + min.y > 0.0f || -e + max.y < 0.0f) return { false };
                }
            }


            {
                glm::vec3 zaxis(modelMatrix[2].x, modelMatrix[2].y, modelMatrix[2].z);
                float e = glm::dot(zaxis, delta);
                float f = glm::dot(direction, zaxis);

                if (fabs(f) > 0.001f) {

                    float t1 = (e + min.z) / f;
                    float t2 = (e + max.z) / f;

                    if (t1 > t2) std::swap(t1, t2);

                    if (t2 < tMax) tMax = t2;
                    if (t1 > tMin) tMin = t1;
                    if (tMin > tMax) return { false };

                }
                else {
                    if (-e + min.z > 0.0f || -e + max.z < 0.0f) return { false };
                }
            }

            return true;
        }
	};

}
#endif
