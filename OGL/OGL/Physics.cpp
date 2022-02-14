#include "Physics.h"

namespace Harmony
{
    bool Physics::Intersection(Cube& _cubeOne, Cube& _cubeTwo)
    {
        float sizeX1 = _cubeOne.Get_High_pos().x - _cubeOne.Get_Low_pos().x;
        float sizeX2 = _cubeTwo.Get_High_pos().x - _cubeTwo.Get_Low_pos().x;
        float sizeY1 = _cubeOne.Get_High_pos().y - _cubeOne.Get_Low_pos().y;
        float sizeY2 = _cubeTwo.Get_High_pos().y - _cubeTwo.Get_Low_pos().y;
        float sizeZ1 = _cubeOne.Get_High_pos().z - _cubeOne.Get_High_neg().z;
        float sizeZ2 = _cubeTwo.Get_High_pos().z - _cubeTwo.Get_High_neg().z;
        //check the X axis
        if (2 * glm::abs(_cubeOne.GetPos().x - _cubeTwo.GetPos().x) <= sizeX1 + sizeX2)
        {
            //check the Y axis
            if (2 * glm::abs(_cubeOne.GetPos().y - _cubeTwo.GetPos().y) <= sizeY1 + sizeY2)
            {
                //check the Z axis
                if (2 * glm::abs(_cubeOne.GetPos().z - _cubeTwo.GetPos().z) <= sizeZ1 + sizeZ2)
                {
                    return true;
                }
            }
        }

        return false;
    }

    bool Physics::Point(Cube& _cubeOne, glm::vec3 _point)
    {
        if (_cubeOne.Get_Low_neg().x <= _point.x &&
            _cubeOne.Get_High_pos().x >= _point.x &&
            _cubeOne.Get_Low_neg().y <= _point.y &&
            _cubeOne.Get_High_pos().y >= _point.y &&
            _cubeOne.Get_Low_neg().z <= _point.z &&
            _cubeOne.Get_High_pos().z >= _point.z
            )
        {
            return true;
        }

        return false;
    }
}

