#pragma once

#include "Types.h"

namespace RenEngine
{
    class InputManager
    {
        public:
            void imStartup();
            void imShutdown();

            void update();
            bool keyPressed(GraphicsManager&, input_code);
    };
}