#include "NumptyBehavior.h"

void CleanupAllPointers();

GLFWwindow* m_RenderWindow;

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main()
{
	float ratio;
	int width = 800, height = 800;

	glfwSetErrorCallback(error_callback);

	// Check if glfw Initalises correctly
	if (!glfwInit())
	{
		std::cout << "Failed to Initalise GLFW" << std::endl;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

	m_RenderWindow = glfwCreateWindow(width, height, "My Title", NULL, NULL);

	if (!m_RenderWindow)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(m_RenderWindow, key_callback);

	glfwMakeContextCurrent(m_RenderWindow);

	while (!glfwWindowShouldClose(m_RenderWindow))
	{
		

		glfwGetFramebufferSize(m_RenderWindow, &width, &height);
		ratio = width / (float)height;

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(m_RenderWindow);
		glfwPollEvents();

	}

	glfwDestroyWindow(m_RenderWindow);

	glfwTerminate();
	exit(EXIT_SUCCESS);
	CleanupAllPointers();
	return NULL;
}

void CleanupAllPointers()
{
	NumptyBehavior::CleanupPointer(m_RenderWindow);
}