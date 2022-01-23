#include "CSquare.h"
#include "MousePicker.h"
#include "ICompList.h"
#include "Cubemap.h"
#include "MeshHandler.h"

static int m_WindowWidth = 1600;
static int m_WindowHeight = 900;

static long double deltaTime = 0.0;	// Time between current frame and last frame
static long double lastFrame = 0.0; // Time of last frame

void InitGLFW();
void InitGLFWCallbacks();
void InitInputMode();
void HandleImGuiMenuBar();
void HandleImGuiDebugInfo();
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

GLFWwindow* m_RenderWindow = nullptr;
Shape::CSquare* m_SquareTest = nullptr;
Cubemap* skybox = nullptr;
Camera m_MainCamera(m_Keypresses, glm::vec3(0.0f, 0.0f, 3.0f));
MeshHandler m_MeshHandler;
MousePicker m_MousePicker(&m_MainCamera);

bool firstMouse = true;
bool m_ShowMouse = false;
static float lastX = 0.0f, lastY = 0.0f;

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos)
{
	m_MousePicker.GrabMousePosition(xPos, yPos);
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
		m_MainCamera.ProcessMouse(xoffset, yoffset);
}

static void cursorEnterCallback(GLFWwindow* window, int entered)
{
	if (m_SquareTest)
	{
		m_SquareTest->CursorEnterCallback(window, entered);
	}
}

static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	// Collect Input
	if (action == GLFW_PRESS)
		m_Mousepresses[button] = true;
	else if (action == GLFW_RELEASE)
		m_Mousepresses[button] = false;

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
		m_Keypresses[key] = true;
	else if (action == GLFW_RELEASE)
		m_Keypresses[key] = false;

	// Object Input
	m_MainCamera.Input();
	if (m_SquareTest)
	{
		m_SquareTest->Input(m_MousePicker.GetCurrentRay(), window, key, scancode, action, mods);
	}
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	float aspect = (float)width / (float)height;
	glViewport(0, 0, width, height);
}

static void window_content_scale_callback(GLFWwindow* window, float xscale, float yscale)
{
}

static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	m_MainCamera.ProcessScroll(yOffset);
}

int main()
{
	InitGLFW();
	GUI::InitImGUI(m_RenderWindow);
	// MAIN START
	Start();

	while (!glfwWindowShouldClose(m_RenderWindow))
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
		std::cout << "Failed to Initalise GLEW" << std::endl;

	// Callbacks
	InitGLFWCallbacks();

	// Input Mode
	InitInputMode();

	// Enables
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
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

void HandleImGuiMenuBar()
{
	ImGui::BeginMenuBar();
	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("Close", "Ctrl+W")) { ISTOOLACTIVE = false; }
		ImGui::EndMenu();
	}
	ImGui::EndMenuBar();

	ImGui::Columns(2);
	ImGui::SetColumnOffset(1, 300);

	ImGuiStyle* style = &ImGui::GetStyle();
	style->WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style->WindowMinSize = ImVec2(900, 480);

	style->FramePadding = ImVec2(8, 6);

	style->Colors[ImGuiCol_TitleBg] = ImColor(255, 101, 53, 255);
	style->Colors[ImGuiCol_TitleBgActive] = ImColor(255, 101, 53, 255);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImColor(0, 0, 0, 255);

	style->Colors[ImGuiCol_Button] = ImColor(31, 30, 31, 255);
	style->Colors[ImGuiCol_ButtonActive] = ImColor(31, 30, 31, 255);
	style->Colors[ImGuiCol_ButtonHovered] = ImColor(41, 40, 41, 255);

	style->Colors[ImGuiCol_Separator] = ImColor(70, 70, 70, 255);
	style->Colors[ImGuiCol_SeparatorActive] = ImColor(70, 70, 70, 255);
	style->Colors[ImGuiCol_SeparatorHovered] = ImColor(76, 76, 76, 255);
}

void HandleImGuiDebugInfo()
{
	std::string frameTime = "Frame Time (seconds) = {";
	frameTime += std::to_string(deltaTime);
	frameTime += "}";

	std::string mousePosX = std::to_string(m_MousePicker.GetCurrentRay().x);
	std::string mousePosZ = std::to_string(m_MousePicker.GetCurrentRay().z);
	std::string mousePosY = std::to_string(m_MousePicker.GetCurrentRay().y);
	std::string mousePos = "Mouse Position(i^,j^,k^) = {";
	mousePos += mousePosX.c_str();
	mousePos += ",";
	mousePos += mousePosY.c_str();
	mousePos += ",";
	mousePos += mousePosZ.c_str();
	mousePos += "}";

	// Camera Position(x,y,z)
	std::string camPosZ = std::to_string(m_MainCamera.Position.z);
	std::string camPosY = std::to_string(m_MainCamera.Position.y);
	std::string camPos = "Main Camera Position(x,y,z) = {";
	camPos += std::to_string(m_MainCamera.Position.x);
	camPos += ",";
	camPos += camPosY.c_str();
	camPos += ",";
	camPos += camPosZ.c_str();
	camPos += "}";

	// Camera Front(x,y,z)
	std::string camFrontZ = std::to_string(m_MainCamera.Front.z);
	std::string camFrontY = std::to_string(m_MainCamera.Front.y);
	std::string camFront = "Main Camera Front(i^,j^,k^) = {";
	camFront += std::to_string(m_MainCamera.Front.x);
	camFront += ",";
	camFront += camFrontY.c_str();
	camFront += ",";
	camFront += camFrontZ.c_str();
	camFront += "}";

	ImGui::NextColumn();
	// Display contents in a scrolling region
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Console Output");
	ImGui::BeginChild("Scrolling");
	// Toggle Camera Light
	ImGui::Text("Camera Spotlight");
	GUI::ToggleButton("CamLight", &m_MainCamera.m_CamLightEnabled);
	ImGui::Text("Mesh Lighting");
	GUI::ToggleButton("MeshLighting", &m_MeshHandler.MESHES[0]->m_LightingEnabled);
	if (ImGui::Button("Recompile All Meshes"))
	{
		std::cout << m_MeshHandler.MESHES[0]->m_LightingEnabled << std::endl;
		m_MeshHandler.RecompileMeshes();
	}
	ImGui::Text(frameTime.c_str());
	ImGui::Text(mousePos.c_str());
	ImGui::Text(camPos.c_str());
	ImGui::Text(camFront.c_str());
	ImGui::EndChild();
}

void Start()
{
	/*if (!m_SquareTest)
		m_SquareTest = new Shape::CSquare(m_Keypresses, m_MainCamera);*/
	
	std::shared_ptr<Mesh> test(new Mesh(m_MainCamera));
	m_MeshHandler.AddMesh(test);

	if (!skybox)
		skybox = new Cubemap(m_MainCamera);
}

void Update()
{
	m_MousePicker.Update();
	HandleImGuiMenuBar();
	CalculateDeltaTime(); 
	InputActions();
	HandleMouseVisible();
	m_MainCamera.Movement(deltaTime);

	if (m_MeshHandler.MESHES.size() > 0)
	{
		if (m_MeshHandler.MESHES[0])
		{
			m_MeshHandler.MESHES[0]->ModifyInstance(1, { m_MainCamera.Position + glm::vec3(m_MainCamera.Front.x * 5, m_MainCamera.Front.y * 5, m_MainCamera.Front.z * 5) });
		}
	}

	if (m_SquareTest)
	{
		m_SquareTest->Update(deltaTime);
	}

	m_MeshHandler.Draw();

	if (skybox)
	{
		skybox->Render();
	}

	HandleImGuiDebugInfo();
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
					m_SquareTest->MarkAsDestroy = true;

				// Only Single Press Thanks
				m_Keypresses[item.first] = false;
				break;
			}
			case GLFW_KEY_L:
			{
				if (!m_SquareTest)
					m_SquareTest = new Shape::CSquare(m_Keypresses, m_MainCamera);

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
		if (m_SquareTest->MarkAsDestroy)
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
	NumptyBehavior::CleanupPointer(skybox);
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
