#pragma once

#define GLFW_INCLUDE_NONE

#include "GLFW/glfw3.h"
#include "GuiManager.h"
#include "GraphicsManager.h"

using namespace RenEngine;

void GuiManager::startup(GraphicsManager& gm)
{
    simgui_setup(simgui_desc_t());
    ImGui_ImplGlfw_InitForOther((GLFWwindow*)gm.getWindow(), true);
}

void GuiManager::shutdown()
{
    ImGui_ImplGlfw_Shutdown();
    simgui_shutdown();
    /*
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();*/
}

void GuiManager::newFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void GuiManager::draw()
{
    ImGui_ImplGlfw_NewFrame();
    ImGui::Begin("ImGui Window");
    ImGui::Text("Hello world");
    ImGui::End();
    simgui_render();
}