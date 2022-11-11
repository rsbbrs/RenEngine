#pragma once

#include "GraphicsManager.h"
#include "GuiManager.h"

#include "imgui_impl_glfw.h"
#include "sokol_app.h"
#include "sokol_gfx.h"
#include "util\sokol_imgui.h"

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

    // GUI stuff

    simgui_render();
}