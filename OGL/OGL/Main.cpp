#include "CSquare.h"

static int m_WindowWidth = 1600;
static int m_WindowHeight = 900;

static long double deltaTime = 0.0;	// Time between current frame and last frame
static long double lastFrame = 0.0; // Time of last frame

void InitGLFW();
void InitGLFWCallbacks();
void InitInputMode();
void Start();
void Update();
void HandleMouseVisible();
void InputActions();
bool CleanupObjects();
int Cleanup();
void CleanupAllPointers();
void CalculateDeltaTime();
void CleanupGLFW();

std::map<int, bool> m_Keypresses;
std::map<int, bool> m_Mousepresses;

GLFWwindow* m_RenderWindow;
CSquare* m_SquareTest;
Camera m_MainCamera(m_Keypresses, glm::vec3(0.0f, 0.0f, 3.0f));

bool firstMouse = true;
bool m_ShowMouse = false;
static float lastX = 0.0f, lastY = 0.0f;

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}
	auto xoffset = xPos - lastX;
	lastX = xPos;

	auto yoffset = lastY - yPos;
	lastY = yPos;

	if (!m_ShowMouse)
		m_MainCamera.ProcessMouseMovement(xoffset, yoffset);
}

static void cursorEnterCallback(GLFWwindow* window, int entered)
{
	if (m_SquareTest)
		m_SquareTest->CursorEnterCallback(window, entered);
}

static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	// Collect Input
	if (action == GLFW_PRESS)
	{
		m_Mousepresses[button] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		m_Mousepresses[button] = false;
	}

	// General Input
	for (auto& item : m_Mousepresses)
	{
		if (item.second == true)
		{
			switch (item.first)
			{
			case GLFW_MOUSE_BUTTON_1:
				// Only Single Press Thanks
				m_Mousepresses[button] = false;
				break;

			default:
				break;
			}
		}
	}
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Collect Input
	if (action == GLFW_PRESS)
	{
		m_Keypresses[key] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		m_Keypresses[key] = false;
	}

	// Object Input
	m_MainCamera.ProcessKeyboard(deltaTime);
	if (m_SquareTest)
		m_SquareTest->Input(window, key, scancode, action, mods);
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	float aspect = (float)width / (float)height;
	glViewport(0, 0, width, height);
}

static void window_content_scale_callback(GLFWwindow* window, float xscale, float yscale)
{
}

static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	m_MainCamera.ProcessMouseScroll(yOffset);
}

int main()
{
	InitGLFW();
	GUI::InitImGUI(m_RenderWindow);
	// MAIN START
	Start();

	while (!glfwWindowShouldClose(m_RenderWindow))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
		glClearDepth(1);
		GUI::StartImGUIFrame();
		//
		// MAIN UPDATE
		Update();
		//
		GUI::EndImGUIFrame();
		glfwSwapBuffers(m_RenderWindow);
		glfwPollEvents();
		CleanupObjects();
	}

	// CLEANUP AND EXIT
	return Cleanup();
}

void InitGLFW()
{
	// Error Callback
	glfwSetErrorCallback(error_callback);

	// Check if glfw Initalises correctly
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "Failed to Initalise GLFW" << std::endl;
	}

	// Setting Version And Profile ; 460 : CORE
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create Render Window
	m_RenderWindow = glfwCreateWindow(m_WindowWidth, m_WindowHeight, "Harmony v0.01", NULL, NULL);

	if (!m_RenderWindow)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Frame Buffer
	glfwGetFramebufferSize(m_RenderWindow, &m_WindowWidth, &m_WindowHeight);

	// Context
	glfwMakeContextCurrent(m_RenderWindow);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to Initalise GLEW" << std::endl;
	}

	// Callbacks
	InitGLFWCallbacks();

	// Input Mode
	InitInputMode();

	// Enables
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void InitGLFWCallbacks()
{
	glfwSetFramebufferSizeCallback(m_RenderWindow, framebuffer_size_callback);
	glfwSetKeyCallback(m_RenderWindow, key_callback);
	glfwSetWindowContentScaleCallback(m_RenderWindow, window_content_scale_callback);
	glfwSetCursorPosCallback(m_RenderWindow, cursorPositionCallback);
	glfwSetCursorEnterCallback(m_RenderWindow, cursorEnterCallback);
	glfwSetMouseButtonCallback(m_RenderWindow, mouseButtonCallback);
	glfwSetScrollCallback(m_RenderWindow, scrollCallback);
}

void InitInputMode()
{
	glfwSetInputMode(m_RenderWindow, GLFW_STICKY_MOUSE_BUTTONS, 1);
	glfwSetInputMode(m_RenderWindow, GLFW_STICKY_KEYS, 1);
}

void Start()
{
	if (!m_SquareTest)
		m_SquareTest = new CSquare(m_Keypresses, m_MainCamera);
	m_SquareTest->Start();

}

void Update()
{
	CalculateDeltaTime(); 
	InputActions();
	HandleMouseVisible();
	m_MainCamera.Movement(deltaTime);
	if (m_SquareTest)
		m_SquareTest->Update(deltaTime);
		m_SquareTest->ImGuiHandler();
}

void HandleMouseVisible()
{
	if (m_ShowMouse)
		glfwSetInputMode(m_RenderWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	else
		glfwSetInputMode(m_RenderWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void InputActions()
{
	// General Input
	for (auto& item : m_Keypresses)
	{
		if (item.second == true)
		{
			switch (item.first)
			{
			case GLFW_KEY_ESCAPE:
				// Close Window
				glfwSetWindowShouldClose(m_RenderWindow, GLFW_TRUE);

				// Only Single Press Thanks
				m_Keypresses[item.first] = false;
				break;
			case GLFW_KEY_TAB:
			{
				m_ShowMouse = !m_ShowMouse;

				// Only Single Press Thanks
				m_Keypresses[item.first] = false;
				break;
			}
			case GLFW_KEY_K:
			{
				if (m_SquareTest)
					m_SquareTest->MARKASDESTROY = true;

				// Only Single Press Thanks
				m_Keypresses[item.first] = false;
				break;
			}
			case GLFW_KEY_L:
			{
				if (!m_SquareTest)
					m_SquareTest = new CSquare(m_Keypresses, m_MainCamera);
					m_SquareTest->Start();

				// Only Single Press Thanks
				m_Keypresses[item.first] = false;
				break;
			}
			default:
				break;
			}
		}
	}
}

bool CleanupObjects()
{
	if (m_SquareTest)
	{
		if (m_SquareTest->MARKASDESTROY)
		{
			delete m_SquareTest;
			m_SquareTest = nullptr;
			return true;
		}
	}
		
	return false;
}

int Cleanup()
{
	GUI::CleanupImGUI();
	CleanupGLFW();
	CleanupAllPointers();

	return NULL;
}

void CleanupAllPointers()
{
	NumptyBehavior::CleanupPointer(m_SquareTest);
	m_Mousepresses.clear();
	m_Keypresses.clear();
	NumptyBehavior::CleanupPointer(m_RenderWindow);
}

void CalculateDeltaTime()
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

void CleanupGLFW()
{
	glfwDestroyWindow(m_RenderWindow);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
