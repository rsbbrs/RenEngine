/*#pragma once

#define SOKOL_IMGUI_IMPL
#define SOKOL_GLCORE33

#include "sokol_app.h"
#include "sokol_gfx.h"
#include "sokol_glue.h"
#include "imgui.h"
#include "util\sokol_imgui.h"

#include "GuiManager.h"

using namespace RenEngine;

void GuiManager::startup()
{
    simgui_desc_t simgui_desc = { };
    simgui_setup(&simgui_desc);
}

void GuiManager::shutdown()
{
    simgui_shutdown();
}

void GuiManager::draw()
{
    simgui_new_frame({ sapp_width(), sapp_height(), sapp_frame_duration(), sapp_dpi_scale() });

    ImGui::Begin("ImGui Window");
    ImGui::Text("Hello world");
    ImGui::End();
    simgui_render();
}*/