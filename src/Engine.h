#pragma once

#include <Types.h>
#include <thread>
#include <chrono>
#include "GraphicsManager.h"

namespace RenEngine
{
    class Engine
    {
        private:
            // Variables used by the engine.
            const std::chrono::duration<double> one_sixtieth_of_a_second;
            Window window;

            // Game managers
            GraphicsManager graphics;
            //InputManager input;

            // Start and shutdown functions.
            // Made private so no other classes can shut down the engine itself.
            void startup();
            void shutdown();

        public:
            // Constructor takes game parameters. Currently only for window size.
            Engine(int, int, const char *, bool);

            // Main game loop.
            void gameLoop();
    };
}