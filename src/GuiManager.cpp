#pragma once

#include "GLFW/glfw3.h"
#include "GuiManager.h"
#include "GraphicsManager.h"

using namespace RenEngine;

void GuiManager::startup(GraphicsManager& gm)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = ImGui::GetIO(); (void) io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)gm.getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void GuiManager::shutdown()
{
    // Does nothing right now.
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
}