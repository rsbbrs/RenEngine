#pragma once

#include "GraphicsManager.h"
#include "GuiManager.h"

#define SOKOL_IMGUI_IMPL
#define SOKOL_IMGUI_NO_SOKOL_APP
#define SOKOL_GLCORE33

#include "imgui_impl_glfw.h"
#include "sokol_app.h"
#include "sokol_gfx.h"
#include "util/sokol_imgui.h"

using namespace RenEngine;

/*
    simgui_setup, simgui_shutdown, and simgui_render aren't found.
    Causes linking error.
*/

void GuiManager::startup(GraphicsManager& manager)
{
    simgui_desc_t simgui_desc = { };
    simgui_setup(&simgui_desc);
    ImGui_ImplGlfw_InitForOther((GLFWwindow*)manager.getWindow(), true);
}

void GuiManager::shutdown()
{
    ImGui_ImplGlfw_Shutdown();
    simgui_shutdown();
}

void GuiManager::draw()
{
    ImGui_ImplGlfw_NewFrame();

    ImGui::Begin("Demo window");
    ImGui::End();

    simgui_render();
}