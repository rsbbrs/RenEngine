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

    ImGui::Text("\nMass:\n");
    ImGui::PushItemWidth(150);
    ImGui::InputFloat("", &rb.mass);
    ImGui::PopItemWidth();

    ImGui::Text("\nForce:\n\tx: %f\t y: %f", rb.force.x, rb.force.y);
    ImGui::Text("Acceleration:\n\tx: %f\t y: %f", rb.acceleration.x, rb.acceleration.y);
    ImGui::Text("Velocity:\n\tx: %f\t y: %f", rb.velocity.x, rb.velocity.y);
    ImGui::Text("Box Collider:\n\tmin: (%.3f, %.3f)\n\tmax (%.3f, %.3f)", rb.min.x, rb.min.y, rb.max.x, rb.max.y);
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

void GuiManager::draw(ECS& ecs, GraphicsManager* gm)
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
    
    ecs.ForEach<Sprite>([&](EntityID e)
    {
        Sprite s = ecs.Get<Sprite>(e);
        Position& p = ecs.Get<Position>(e);
        Scale& sc = ecs.Get<Scale>(e);
        Rotation& rot = ecs.Get<Rotation>(e);

        ImGui::PushID(e);

        if(ImGui::CollapsingHeader(s.name.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Text("Position:\n");
            ImGui::PushItemWidth(75);
            ImGui::InputFloat("x", &p.x);
            ImGui::SameLine();
            ImGui::InputFloat("y", &p.y);
            ImGui::SameLine();
            ImGui::InputFloat("z", &p.z);
            ImGui::PopItemWidth();

            ImGui::Text("Scale:\n");
            if(ImGui::DragInt("Size", &sc.scale, 0.5, 0, 100))
                gm->getBoxCollider(s.name, p, sc.scale, ecs.Get<RigidBody>(e).min, ecs.Get<RigidBody>(e).max);

            ImGui::Text("Rotation:\n");
            ImGui::DragFloat("Angle", &rot.angle, 0.5, 0.0, 360.0);

            //Rigid body objects
            rigidBody(e, ecs);
        }

        ImGui::PopID();
    });

    ImGui::End();
    
    simgui_render();
}