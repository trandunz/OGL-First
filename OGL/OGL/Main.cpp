#include "CTriangle.h"
#include "CCamera.h"
#include "Singleton.h"

static int m_WindowWidth = 1600;
static int m_WindowHeight = 900;

GLfloat halfScreenWidth = 1920 / 2;
GLfloat halfScreenHeight = 1080 / 2;

static long double deltaTime = 0.0;	// Time between current frame and last frame
static long double lastFrame = 0.0; // Time of last frame

void InitCursor();
void InitGLFW();
void Start();
void Update();
void CleanupAllPointers();
void CalculateDeltaTime();

GLFWwindow* m_RenderWindow;
CTriangle* m_TriangleTest;
CCamera m_MainCamera;


std::map<int, bool> m_Keypresses;
std::map<int, bool> m_Mousepresses;

glm::mat4 m_ViewModelMatrix = m_MainCamera.GetViewMatrix();

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos)
{
	m_MainCamera.MouseInput(window, xPos, yPos);
}

static void cursorEnterCallback(GLFWwindow* window, int entered)
{
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
				// Close Window
				glfwSetWindowShouldClose(window, GLFW_TRUE);

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

	// General Input
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

	m_MainCamera.Input(window, key, scancode, action, mods);
		
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
	m_MainCamera.ScrollInput(window, yOffset);
}

int main()
{
	// MAIN START
	Start();

	while (!glfwWindowShouldClose(m_RenderWindow))
	{
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

void InitCursor()
{
	unsigned char pixels[16 * 16 * 4];
	memset(pixels, 0xff, sizeof(pixels));
	GLFWimage image;
	image.width = 16;
	image.height = 16;
	image.pixels = pixels;
	GLFWcursor* cursor = glfwCreateCursor(&image, 0, 0);
	glfwSetCursor(m_RenderWindow, cursor);
}

void InitGLFW()
{
	glfwSetErrorCallback(error_callback);

	// Check if glfw Initalises correctly
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "Failed to Initalise GLFW" << std::endl;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_RenderWindow = glfwCreateWindow(m_WindowWidth, m_WindowHeight, "My Title", NULL, NULL);

	if (!m_RenderWindow)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwGetFramebufferSize(m_RenderWindow, &m_WindowWidth, &m_WindowHeight);

	// Context
	glfwMakeContextCurrent(m_RenderWindow);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to Initalise GLEW" << std::endl;
	}

	// Callbacks
	glfwSetFramebufferSizeCallback(m_RenderWindow, framebuffer_size_callback);
	glfwSetKeyCallback(m_RenderWindow, key_callback);
	glfwSetWindowContentScaleCallback(m_RenderWindow, window_content_scale_callback);
	glfwSetCursorPosCallback(m_RenderWindow, cursorPositionCallback);
	glfwSetCursorEnterCallback(m_RenderWindow, cursorEnterCallback);
	glfwSetMouseButtonCallback(m_RenderWindow, mouseButtonCallback);
	glfwSetScrollCallback(m_RenderWindow, scrollCallback);

	// Input Mode
	glfwSetInputMode(m_RenderWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// Sticky Buffers Input Until The End OF Frame To Avoid Missed Ones
	glfwSetInputMode(m_RenderWindow, GLFW_STICKY_MOUSE_BUTTONS, 1);
	glfwSetInputMode(m_RenderWindow, GLFW_STICKY_KEYS, 1);
	
	// View Port Nonsense
	glViewport(0.0f, 0.0f, m_WindowWidth, m_WindowHeight); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
	glMatrixMode(GL_PROJECTION); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
	glLoadIdentity(); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
	glOrtho(0, m_WindowWidth, 0, m_WindowHeight, 0, 1000); // essentially set coordinate system
	glMatrixMode(GL_MODELVIEW); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
	glLoadIdentity(); // same as above comment

	//glfwSetWindowAspectRatio(m_RenderWindow, 16, 9);
	//glfwSwapInterval(0.1f);


}

void Start()
{
	InitGLFW();
	InitCursor();

	if (!m_TriangleTest)
		m_TriangleTest = new CTriangle(m_Keypresses);
	m_TriangleTest->Start();

	m_MainCamera.SetKeyMap(m_Keypresses);
}

void Update()
{
	CalculateDeltaTime(); 

	m_MainCamera.Update(deltaTime);

	m_TriangleTest->Update(deltaTime, m_MainCamera);
}

void CleanupAllPointers()
{
	NumptyBehavior::CleanupPointer(m_TriangleTest);
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