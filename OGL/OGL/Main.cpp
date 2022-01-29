#include "Cubemap.h"
#include "FrameBuffer.h"
#include "Entity.h"

static int m_WindowWidth = 1600;
static int m_WindowHeight = 900;

static double deltaTime = 0.0;	// Time between current frame and last frame
static double lastFrame = 0.0; // Time of last frame
static unsigned int frameCounter = 0;

using namespace Harmony;

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
TextureMaster m_TextureMaster;
FrameBuffer* m_FrameBuffer = nullptr;

Scene m_Scene;
Entity m_CamEntity;
Entity m_TestEntity;
Entity m_MousePickEntity;
Entity m_CubemapEntity;

bool firstMouse = true;
bool m_ShowMouse = false;
static float lastX = 0.0f, lastY = 0.0f;

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos)
{
	m_MousePickEntity.GetComponent<MousePickerComponent>().MousePicker.GrabMousePosition(xPos, yPos);
	if (firstMouse)
	{
		lastX = (float)xPos;
		lastY = (float)yPos;
		firstMouse = false;
	}
	auto xoffset = (float)xPos - lastX;
	lastX = (float)xPos;

	auto yoffset = lastY - yPos;
	lastY = (float)yPos;

	if (!m_ShowMouse)
		m_CamEntity.GetComponent<CameraComponent>().Camera.ProcessMouse((float)xoffset, (float)yoffset);
}

static void cursorEnterCallback(GLFWwindow* window, int entered)
{
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
	if (m_CamEntity.HasComponent< CameraComponent>())
		m_CamEntity.GetComponent<CameraComponent>().Camera.Input();
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
	m_CamEntity.GetComponent<CameraComponent>().Camera.ProcessScroll((float)yOffset);
}

int main()
{
	InitGLFW();
	GUI::InitImGUI(m_RenderWindow);
	// MAIN START
	Start();

	while (!glfwWindowShouldClose(m_RenderWindow))
	{
		//m_FrameBuffer->Bind();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearDepth(1);
		GUI::StartImGUIFrame();
		//
		// MAIN UPDATE
		Update();
		//
		GUI::EndImGUIFrame();
		//m_FrameBuffer->Draw();
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

	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

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

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	//glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSwapInterval(0);
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
	if (m_TestEntity.IsAlive())
	{
		if (m_TestEntity.HasComponent<MeshComponent>())
		{
			m_TestEntity.GetComponent<MeshComponent>().Mesh.ImGuiHandler();
		}
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
	MousePicker& mousePicker = m_MousePickEntity.GetComponent<MousePickerComponent>();
	Camera& m_Camera = m_CamEntity.GetComponent<CameraComponent>();

	std::string frameTime = "Fps = {";
	frameTime += std::to_string((1 / deltaTime) * frameCounter);
	frameTime += "}\n";
	frameTime += "Frame Time (ms) = {";
	frameTime += std::to_string((deltaTime * frameCounter) * 1000);
	frameTime += "}";
	frameCounter = 0;

	std::string mousePosX = std::to_string(mousePicker.GetCurrentRay().x);
	std::string mousePosZ = std::to_string(mousePicker.GetCurrentRay().z);
	std::string mousePosY = std::to_string(mousePicker.GetCurrentRay().y);
	std::string mousePos = "Mouse Position(i^,j^,k^) = {";
	mousePos += mousePosX.c_str();
	mousePos += ",";
	mousePos += mousePosY.c_str();
	mousePos += ",";
	mousePos += mousePosZ.c_str();
	mousePos += "}";

	// Camera Position(x,y,z)
	std::string camPosZ = std::to_string(m_Camera.Position.z);
	std::string camPosY = std::to_string(m_Camera.Position.y);
	std::string camPos = "Main Camera Position(x,y,z) = {";
	camPos += std::to_string(m_Camera.Position.x);
	camPos += ",";
	camPos += camPosY.c_str();
	camPos += ",";
	camPos += camPosZ.c_str();
	camPos += "}";

	// Camera Front(x,y,z)
	std::string camFrontZ = std::to_string(m_Camera.Front.z);
	std::string camFrontY = std::to_string(m_Camera.Front.y);
	std::string camFront = "Main Camera Front(i^,j^,k^) = {";
	camFront += std::to_string(m_Camera.Front.x);
	camFront += ",";
	camFront += camFrontY.c_str();
	camFront += ",";
	camFront += camFrontZ.c_str();
	camFront += "}";

	m_Camera.ImGUIHandler();

	ImGui::NextColumn();
	// Display contents in a scrolling region
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Console Output");
	ImGui::BeginChild("Scrolling");
	// Toggle Camera Light
	ImGui::Text("Camera Spotlight");
	GUI::ToggleButton("CamLight", &m_Camera.m_CamLightEnabled);
	
	{
		auto view = m_Scene.GetReg().view<MeshComponent>();
		for (auto entity : view)
		{
			auto& mesh = view.get<MeshComponent>(entity);
			ImGui::Text("Mesh Lighting");
			GUI::ToggleButton("MeshLighting", &mesh.Mesh.m_LightingEnabled);
			if (ImGui::Button("Recompile All Meshes"))
			{
				mesh.Mesh.RAW_Recompile();
			}
		}
	}

	ImGui::Text(frameTime.c_str());
	ImGui::Text(mousePos.c_str());
	ImGui::Text(camPos.c_str());
	ImGui::Text(camFront.c_str());
	ImGui::EndChild();
}

void Start() 
{
	m_TextureMaster.LoadTexture("Resources/Textures/planks.png");
	m_TextureMaster.LoadNormal("Resources/Textures/normal.png");
	m_TextureMaster.LoadSpecular("Resources/Textures/planksSpec.png");
	m_TextureMaster.LoadTexture("Resources/Textures/3.jpg");
	m_TextureMaster.LoadTexture("Resources/Textures/diffuse.png");

	m_CamEntity = m_Scene.CreateEntity("MainCamera");
	m_MousePickEntity = m_Scene.CreateEntity("MousePicker");
	m_TestEntity = m_Scene.CreateEntity("Meshes");
	m_CubemapEntity = m_Scene.CreateEntity("Skybox");

	Camera m_Camera{ m_Keypresses, glm::vec3(0.0f, 0.0f, 3.0f) };
	auto& camRef = m_CamEntity.AddComponent<CameraComponent>(m_Camera);
	MousePicker picker{ &camRef.Camera };
	auto& pickerRef = m_MousePickEntity.AddComponent<MousePickerComponent>(picker);
	auto& meshRef = m_TestEntity.AddComponent<MeshComponent>(camRef,m_TextureMaster);
	auto& skyboxRef = m_CubemapEntity.AddComponent<CubemapComponent>(camRef);
}

void Update()
{
	HandleImGuiMenuBar();
	CalculateDeltaTime();
	InputActions();
	HandleMouseVisible();

	{
		auto view = m_Scene.GetReg().view<MeshComponent>();
		for (auto entity : view)
		{
			auto& mesh = view.get<MeshComponent>(entity);
			mesh.Mesh.RAW_Draw();
		}
	}
	{
		auto view = m_Scene.GetReg().view<CubemapComponent>();
		for (auto entity : view)
		{
			auto& mesh = view.get<CubemapComponent>(entity);
			mesh.Cubemap.Render();
		}
	}
	{
		auto view = m_Scene.GetReg().view<CameraComponent>();
		for (auto entity : view)
		{
			auto& mesh = view.get<CameraComponent>(entity);
			mesh.Camera.Movement(deltaTime);
		}
	}
	{
		auto view = m_Scene.GetReg().view<MousePickerComponent>();
		for (auto entity : view)
		{
			auto& mesh = view.get<MousePickerComponent>(entity);
			mesh.MousePicker.Update();
		}
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
			case GLFW_KEY_O:
			{
				if (m_CubemapEntity.IsAlive())
				{
					m_CubemapEntity.Destory();
				}

				// Only Single Press Thanks
				m_Keypresses[item.first] = false;
				break;
			}
			case GLFW_KEY_P:
			{

				if (!m_CubemapEntity.IsAlive())
				{
					m_CubemapEntity = m_Scene.CreateEntity("Skybox");

					if (!m_CubemapEntity.HasComponent<CubemapComponent>())
					{
						auto& camRef = m_CamEntity.GetComponent<CameraComponent>();
						m_CubemapEntity.AddComponent<CubemapComponent>(camRef);
					}
				}

				// Only Single Press Thanks
				m_Keypresses[item.first] = false;
				break;
			}
			case GLFW_KEY_K:
			{
				if (m_TestEntity.IsAlive())
				{
					m_TestEntity.Destory();
				}

				// Only Single Press Thanks
				m_Keypresses[item.first] = false;
				break;
			}
			case GLFW_KEY_L:
			{
				if (!m_TestEntity.IsAlive())
				{
					m_TestEntity = m_Scene.CreateEntity("Mesh");

					if (!m_TestEntity.HasComponent<MeshComponent>())
					{
						auto& camRef = m_CamEntity.GetComponent<CameraComponent>();
						m_TestEntity.AddComponent<MeshComponent>(camRef, m_TextureMaster);
					}
				}
				
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
	m_CubemapEntity.Destory();
	m_CamEntity.Destory();
	m_TestEntity.Destory();
	m_MousePickEntity.Destory();
	m_Mousepresses.clear();
	m_Keypresses.clear();
	if (m_FrameBuffer)
	{
		delete m_FrameBuffer;
		
	}
	m_FrameBuffer = nullptr;
	if (m_RenderWindow)
	{
		delete m_RenderWindow;

	}
	m_RenderWindow = nullptr;
}

void CalculateDeltaTime()
{
	float currentFrame = (float)glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	frameCounter++;
}

void CleanupGLFW()
{
	glfwDestroyWindow(m_RenderWindow);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
