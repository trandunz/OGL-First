#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <GLM/gtc/quaternion.hpp>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <unordered_map>
#include <charconv>

#include <entt/entt.hpp>

static void Print(std::string_view _string)
{
	std::cout << _string << std::endl;
}

