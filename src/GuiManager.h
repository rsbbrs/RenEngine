#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Types.h"

namespace RenEngine
{
    class GuiManager
    {
        private:
            ImGuiIO& io;

        public:
            GuiManager();
            void startup(GraphicsManager& gm);
            void shutdown();
            void newFrame();
            void drawUI();
    };
}