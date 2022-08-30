#pragma once

#include <Types.h>

namespace RenEngine
{
    class Engine
    {
        private:
            //GraphicsManager graphics;
            //InputManager input;

        public:
            void Startup();
            void Shutdown();
            void GameLoop();
    };
}