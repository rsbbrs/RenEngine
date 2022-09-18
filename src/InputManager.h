#pragma once

#include "Types.h"

namespace RenEngine
{
    class InputManager
    {
        public:
            // Startup and shutdown routines
            void imStartup();
            void imShutdown();

            // Input handling functions.
            void update();
            bool keyPressed(GraphicsManager& gm, input_code key);
    };
}