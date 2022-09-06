#pragma once

// C++ libraries
#include <thread>
#include <chrono>
#include <functional>

// My own types
#include <Types.h>
#include <Declarations.h>

// Managers
#include <GraphicsManager.h>
#include <InputManager.h>
#include <ResourceManager.h>
#include <SoundManager.h>

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
            ResourceManager resources;
            SoundManager sound;

            // Start and shutdown functions.
            // Made private so no other classes can shut down the engine itself.
            void startup();
            void shutdown();

        public:            
            // Constructor takes game parameters. Currently only for window size.
            Engine(int, int, const char *, bool);

            // Main game loop.
            void gameLoop(const UpdateCallback&);

            // Functions used so users can access certain engine functionality
            // Input manager pass through.
            bool keyPressed(input_code);

            // Sound manager pass through.
            void loadSound(const std::string&, const std::string&);
            void playSound(const std::string&);
            void closeSound(const std::string&);

            // Resource manager pass through.
            std::string filePath(std::string);
    };
}