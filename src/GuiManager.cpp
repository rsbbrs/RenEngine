#pragma once

#define GLFW_INCLUDE_NONE
#define SOKOL_IMGUI_IMPL
#define SOKOL_GLCORE33

#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "sokol_app.h"
#include "sokol_gfx.h"
#include "util\sokol_imgui.h"
#include "GuiManager.h"
#include "GraphicsManager.h"

using namespace RenEngine;

void GuiManager::startup(GraphicsManager& gm)
{
    simgui_desc_t description = {0};
    simgui_setup(&description);
    ImGui_ImplGlfw_InitForOther((GLFWwindow*)gm.getWindow(), true);
}

void GuiManager::shutdown()
{
    ImGui_ImplGlfw_Shutdown();
    simgui_shutdown();
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void GuiManager::newFrame()
{
    
}

void GuiManager::draw()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("ImGui Window");
    ImGui::Text("Hello world");
    ImGui::End();
    simgui_render();
}