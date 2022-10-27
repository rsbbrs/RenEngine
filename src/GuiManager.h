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

        public:
            void startup(GraphicsManager& gm);
            void shutdown();
            void newFrame();
            void UI();
            void render();
            void draw();
    };
}