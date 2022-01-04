#include "CTriangle.h"
#include "CProp.h"

static int m_WindowWidth = 800;
static int m_WindowHeight = 800;

static float deltaTime = 0.0f;	// Time between current frame and last frame
static float lastFrame = 0.0f; // Time of last frame

void InitGLFW();
void Start();
void Update();
void CleanupAllPointers();
void CalculateDeltaTime();

GLFWwindow* m_RenderWindow;
CTriangle* m_TriangleTest;
std::vector<CProp*> m_Props;

std::map<int, bool> m_Keypresses;

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// General Input
	if (action == GLFW_PRESS)
	{
		m_Keypresses[key] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		m_Keypresses[key] = false;
	}

	for (auto& item : m_Keypresses)
	{
		if (item.second == true)
		{
			switch (item.first)
			{
			case GLFW_KEY_ESCAPE:
				// Close Window
				glfwSetWindowShouldClose(window, GLFW_TRUE);

				// Only Single Press Thanks
				m_Keypresses[key] = false;
				break;
			default:
				break;
			}
		}
	}

	// Object Input
	m_TriangleTest->Input(window, key, scancode, action, mods);
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

static void window_content_scale_callback(GLFWwindow* window, float xscale, float yscale)
{
	//set_interface_scale(xscale, yscale);
}

int main()
{
	// MAIN START
	Start();

	while (!glfwWindowShouldClose(m_RenderWindow))
	{

		glfwGetFramebufferSize(m_RenderWindow, &m_WindowWidth, &m_WindowHeight);
		glViewport(0, 0, m_WindowWidth, m_WindowHeight);
		glfwSetFramebufferSizeCallback(m_RenderWindow, framebuffer_size_callback);
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
	if (glfwInit() == GLFW_FALSE)
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
	glfwSetWindowContentScaleCallback(m_RenderWindow, window_content_scale_callback);
	glfwMakeContextCurrent(m_RenderWindow);
	glfwSetWindowAspectRatio(m_RenderWindow, 16, 9);

	glfwSwapInterval(0.1f);

	if (!glewInit() == GLFW_FALSE)
	{
		std::cout << "Failed to Initalise GLEW" << std::endl;
	}
}

void Start()
{
	InitGLFW();

	if (!m_TriangleTest)
		m_TriangleTest = new CTriangle;
	m_TriangleTest->Start();

	m_Props.push_back(new CProp);
	m_Props.back()->Start();
}

void Update()
{
	CalculateDeltaTime();

	m_TriangleTest->Update(deltaTime, m_RenderWindow);
	for (auto& item : m_Props)
	{
		item->Update();
	}
}

void CleanupAllPointers()
{
	NumptyBehavior::CleanupPointer(m_RenderWindow);
	NumptyBehavior::CleanupPointer(m_TriangleTest);

	for (auto& item : m_Props)
	{
		NumptyBehavior::CleanupPointer(item);
	}
	m_Props.clear();
}

void CalculateDeltaTime()
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}