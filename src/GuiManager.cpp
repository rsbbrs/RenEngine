#pragma once

#include "GraphicsManager.h"
#include "ECS.h"
#include "GuiManager.h"

#define SOKOL_IMGUI_IMPL
#define SOKOL_IMGUI_NO_SOKOL_APP
#define SOKOL_GLCORE33

#include "imgui_impl_glfw.h"
#include "sokol_gfx.h"
#include "util/sokol_imgui.h"

using namespace RenEngine;

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

void GuiManager::draw(ECS& manager)
{
    ImGui_ImplGlfw_NewFrame();
    ImGuiIO& io = ImGui::GetIO();

    simgui_frame_desc_t desc;
    desc.width = io.DisplaySize.x;
    desc.height = io.DisplaySize.y;
    desc.delta_time = io.DeltaTime;
    desc.dpi_scale = 1.2f;
    simgui_new_frame(&desc);

    // GUI stuff goes here.
    ImGui::Begin("Object Viewer");
    
    manager.ForEach<RigidBody>([&](EntityID e)
    {
        RigidBody rb = manager.Get<RigidBody>(e);
        Position p = manager.Get<Position>(e);
        Sprite s = manager.Get<Sprite>(e);

        ImGui::Text("Object Name: %s", s.name);
    });

    ImGui::End();
    
    simgui_render();
}