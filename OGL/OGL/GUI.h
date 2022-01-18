#pragma once
#include "NumptyBehavior.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

static bool ISTOOLACTIVE = true;

class GUI :
    public NumptyBehavior
{
public:
	GUI() { ISTOOLACTIVE = true; }
	
    static void InitImGUI(GLFWwindow* _window)
    {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		ImGui_ImplGlfw_InitForOpenGL(_window, true);
		ImGui_ImplOpenGL3_Init("#version 460");
		ImGui::StyleColorsDark();
    }
	static void StartImGUIFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Tools V0.01", &ISTOOLACTIVE, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);
	}
	static void EndImGUIFrame()
	{
		ImGui::End();
		ImGuiRender();
	}
	static void ImGuiRender()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	static void CleanupImGUI()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
};

