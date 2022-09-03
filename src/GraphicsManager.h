#define GLFW_INCLUDE_NONE
#pragma once

#include "GLFW/glfw3.h"
#include <Types.h>

namespace RenEngine
{
    class GraphicsManager
    {
        private: 
            GLFWwindow* window;
            friend class InputManager;

        public:
            void gmStartup(Configuration);
            void gmShutdown();
            bool closeWindow();
    };
}