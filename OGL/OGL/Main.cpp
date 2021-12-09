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
	int width = 800, height = 800;

	glfwSetErrorCallback(error_callback);

	// Check if glfw Initalises correctly
	if (!glfwInit())
	{
		std::cout << "Failed to Initalise GLFW" << std::endl;
	}

	if (!glewInit())
	{
		std::cout << "Failed to Initalise GLEW" << std::endl;
	}

	// Set Context version to OpenGL 3.2
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

	// Create Render Window
	m_RenderWindow = glfwCreateWindow(width, height, "OGL-Project", NULL, NULL);

	// Exit Safely if Render Window doesnt Initalise Properly
	if (!m_RenderWindow)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Set Key Input Callback
	glfwSetKeyCallback(m_RenderWindow, key_callback);

	glfwMakeContextCurrent(m_RenderWindow);

	// Main Update & Render Loop
	while (!glfwWindowShouldClose(m_RenderWindow))
	{

		glfwGetFramebufferSize(m_RenderWindow, &width, &height);

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		//Swap Buffers at the start of each frame
		glfwSwapBuffers(m_RenderWindow);
		glfwPollEvents();

		// Body 


		

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