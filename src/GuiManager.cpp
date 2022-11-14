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

void rigidBody(EntityID e, ECS& manager)
{
    RigidBody& rb = manager.Get<RigidBody>(e);
    Position& p = manager.Get<Position>(e);

    ImGui::Text("Position:\n");
    ImGui::PushItemWidth(75);
    ImGui::InputFloat("x", &p.x);
    ImGui::SameLine();
    ImGui::InputFloat("y", &p.y);
    ImGui::SameLine();
    ImGui::InputFloat("z", &p.z);
    ImGui::PopItemWidth();

    ImGui::PushItemWidth(150);
    ImGui::InputFloat("Mass", &rb.mass);
    ImGui::PopItemWidth();

    ImGui::Text("Force:\n\tx: %f\t y: %f", rb.force.x, rb.force.y);
    ImGui::Text("Acceleration:\n\tx: %f\t y: %f", rb.acceleration.x, rb.acceleration.y);
    ImGui::Text("Velocity:\n\tx: %f\t y: %f", rb.velocity.x, rb.velocity.y);

}

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
    desc.width = (int)io.DisplaySize.x;
    desc.height = (int)io.DisplaySize.y;
    desc.delta_time = io.DeltaTime;
    desc.dpi_scale = 1.0f;
    simgui_new_frame(&desc);

    // GUI stuff goes here.
    ImGui::Begin("Object Viewer");
    
    manager.ForEach<Sprite>([&](EntityID e)
    {
        Sprite s = manager.Get<Sprite>(e);
        if(ImGui::CollapsingHeader(s.name.c_str()))
        {
            //Rigid body objects
            rigidBody(e, manager);
        }
    });

    ImGui::End();
    
    simgui_render();
}