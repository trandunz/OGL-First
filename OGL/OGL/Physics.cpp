#include "Physics.h"

bool Physics::AABB(Cube& _cubeOne, Cube& _cubeTwo)
{
    if (_cubeOne.Get_Low_neg().x <= _cubeTwo.Get_High_pos().x &&
        _cubeOne.Get_High_pos().x >= _cubeTwo.Get_Low_neg().x &&
        _cubeOne.Get_Low_neg().y <= _cubeTwo.Get_High_pos().y &&
        _cubeOne.Get_High_pos().y >= _cubeTwo.Get_Low_neg().y &&
        _cubeOne.Get_Low_neg().z <= _cubeTwo.Get_High_pos().z &&
        _cubeOne.Get_High_pos().z >= _cubeTwo.Get_Low_neg().z
        )
    {
        return true;
    }
    else if (_cubeOne.Get_Low_neg().x <= _cubeTwo.Get_High_pos_op().x &&
        _cubeOne.Get_High_pos_op().x >= _cubeTwo.Get_Low_neg_op().x &&
        _cubeOne.Get_Low_neg_op().y <= _cubeTwo.Get_High_pos_op().y &&
        _cubeOne.Get_High_pos_op().y >= _cubeTwo.Get_Low_neg_op().y &&
        _cubeOne.Get_Low_neg_op().z <= _cubeTwo.Get_High_pos_op().z &&
        _cubeOne.Get_High_pos_op().z >= _cubeTwo.Get_Low_neg_op().z
        )
    {

    }
    else
    {
        return false;
    }
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
    else if (_cubeOne.Get_Low_neg_op().x <= _point.x &&
        _cubeOne.Get_High_pos_op().x >= _point.x &&
        _cubeOne.Get_Low_neg_op().y <= _point.y &&
        _cubeOne.Get_High_pos_op().y >= _point.y &&
        _cubeOne.Get_Low_neg_op().z <= _point.z &&
        _cubeOne.Get_High_pos_op().z >= _point.z
        )
    {
        return true;
    }
    else
    {
        return false;
    }
}
