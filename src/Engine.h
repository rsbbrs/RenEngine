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

            /*****************************************************************************/
            /*                                                                           */
            /* Functions created so users can access certain engine functionality        */
            /* Mainly just pass through functions for the different manager's functions. */
            /*                                                                           */
            /*****************************************************************************/
            
            // Input manager pass throughs.
            bool queryInput(input_code);

            // Sound manager pass throughs.
            void loadSound(const std::string&, const std::string&);
            void playSound(const std::string&);
            void closeSound(const std::string&);

            // Resource manager pass throughs.
            std::string filePath(std::string);
    };
}