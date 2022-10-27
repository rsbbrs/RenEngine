#pragma once

#define GLFW_INCLUDE_NONE

#include "GLFW/glfw3.h"
#include "GuiManager.h"
#include "GraphicsManager.h"

using namespace RenEngine;

void GuiManager::startup(GraphicsManager& gm)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)gm.getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();
}

void GuiManager::shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void GuiManager::newFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void GuiManager::drawUI()
{
    ImGui::Begin("ImGui Window");
    ImGui::Text("Hello world");
    ImGui::End();

    ImGui::Render();
}

void GuiManager::render()
{
    ImGui::Render();
}

void GuiManager::draw()
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}