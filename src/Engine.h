#pragma once

// C++ libraries
#include <thread>
#include <chrono>
#include <functional>

// My own types
#include <Types.h>

// Managers
#include <GraphicsManager.h>
#include <InputManager.h>

namespace RenEngine
{
    class Engine
    {
        typedef std::function<void()> UpdateCallback;

        private:
            // Variables used by the engine.
            const std::chrono::duration<double> total_loop_time;
            Configuration config;

            // Game managers.
            GraphicsManager graphics;
            InputManager input;

            // Start and shutdown functions.
            // Made private so no other classes can shut down the engine itself.
            void startup();
            void shutdown();
            void processInput();

        public:
            // Constructor takes game parameters. Currently only for window size.
            Engine(int, int, const char *, bool);

            // Main game loop.
            void gameLoop(const UpdateCallback&);
    };
}