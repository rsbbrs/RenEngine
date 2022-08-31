#pragma once

#include <Types.h>

namespace RenEngine
{
    class Engine
    {
        private:
            Window window;
            //GraphicsManager graphics;
            //InputManager input;
            void Startup(Window);
            void Shutdown();

        public:
            Engine(int, int, const char *, bool);

            void GameLoop();
    };
}