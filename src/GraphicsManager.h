#pragma once

#include <Types.h>

namespace RenEngine
{
    class GraphicsManager
    {
        private: 
            GLFWwindow *window;
            friend class InputManager;

        public:
            void gmStartup(Window);
            void gmShutdown();
    };
}