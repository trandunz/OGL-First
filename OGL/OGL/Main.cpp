#include <iostream>
#include <GLFW/glfw3.h>

int main()
{
	float ratio;
	int width = 800, height = 800;
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

	// Check if glfw Initalises correctly
	if (!glfwInit())
	{
		std::cout << "Failed to Initalise GLFW" << std::endl;
	}

	GLFWwindow* window = glfwCreateWindow(width, height, "My Title", NULL, NULL);

	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window))
	{
		

		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
	return NULL;
}