#include "CCircle.h"
#include "CTriangle.h"

static int m_WindowWidth = 800;
static int m_WindowHeight = 800;

void InitGLFW();
void Start();
void Update();
void CleanupAllPointers();

GLFWwindow* m_RenderWindow;
CCircle* m_CircleTest;
CTriangle* m_TriangleTest;



static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	
	//m_CircleTest->Input(window, key, scancode, action, mods);
	m_TriangleTest->Input(window, key, scancode, action, mods);
}

int main()
{
	// MAIN START
	Start();

	while (!glfwWindowShouldClose(m_RenderWindow))
	{
		glfwGetFramebufferSize(m_RenderWindow, &m_WindowWidth, &m_WindowHeight);
		glViewport(0, 0, m_WindowWidth, m_WindowHeight);
		glClear(GL_COLOR_BUFFER_BIT);
		//
		// MAIN UPDATE
		Update();
		//
		glfwSwapBuffers(m_RenderWindow);
		glfwPollEvents();
	}

	// CLEANUP
	glfwDestroyWindow(m_RenderWindow);
	glfwTerminate();
	exit(EXIT_SUCCESS);
	CleanupAllPointers();
	return NULL;
}

void InitGLFW()
{
	glfwSetErrorCallback(error_callback);

	// Check if glfw Initalises correctly
	if (!glfwInit())
	{
		std::cout << "Failed to Initalise GLFW" << std::endl;
	}

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	m_RenderWindow = glfwCreateWindow(m_WindowWidth, m_WindowHeight, "My Title", NULL, NULL);

	if (!m_RenderWindow)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(m_RenderWindow, key_callback);

	glfwMakeContextCurrent(m_RenderWindow);
	glfwSwapInterval(1);

	if (!glewInit())
	{
		std::cout << "Failed to Initalise GLEW" << std::endl;
	}
}

void Start()
{
	InitGLFW();

	/*if (!m_CircleTest)
		m_CircleTest = new CCircle;
	m_CircleTest->Start();*/

	if (!m_TriangleTest)
		m_TriangleTest = new CTriangle;
	m_TriangleTest->Start();
}

void Update()
{
	//m_CircleTest->Update();
	m_TriangleTest->Update();
}

void CleanupAllPointers()
{
	NumptyBehavior::CleanupPointer(m_RenderWindow);
	NumptyBehavior::CleanupPointer(m_CircleTest);
	NumptyBehavior::CleanupPointer(m_TriangleTest);
}