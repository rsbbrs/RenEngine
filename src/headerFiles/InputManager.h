#pragma once

#include "Types.h"

namespace RenEngine
{
    class InputManager
    {
        public:
            // Startup and shutdown routines
            void startup();
            void shutdown();

            // Input handling functions.
            void update();
            bool keyPressed(GraphicsManager& gm, input_code key);
            bool keyReleased(GraphicsManager& gm, input_code key);
    };
}