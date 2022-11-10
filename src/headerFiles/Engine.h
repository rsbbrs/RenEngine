#pragma once

// C++ libraries
#include <thread>
#include <chrono>
#include <functional>

// My own types
#include "Types.h"

// Managers
#include "GraphicsManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "ECS.h"
#include "ScriptManager.h"
//#include "GuiManager.h"

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
            GraphicsManager graphicsManager;
            InputManager inputManager;
            ResourceManager resourceManager;
            SoundManager soundManager;
            ECS ECSManager;
            ScriptManager scriptManager;
            //GuiManager guiManager;

            // Start and shutdown functions.
            // Made private so no other classes can shut down the engine itself.
            void startup();
            void shutdown();

        public:            
            /**
             * @brief Construct a new Engine object.
             * 
             * @param name The desired name of the game engine window.
             *             Default is RenEngine.
             * @param width Engine window width. Default is 1280.
             * @param height Engine window height. Default is 720.
             * @param fullscreen Determines if engine window is fullscreen
             *                   or not. Default is false.
             */
            Engine(const char* name = "RenEngine", int width = 1280, int height = 720, bool fullscreen = false);

            /**
             * @brief Main game loop.
             * 
             * @param callback Used to pass custom functions that can run
             *                 inside the main game loop.
             */
            void gameLoop(const UpdateCallback& callback);

            /*****************************************************************************/
            /*                                                                           */
            /* Functions created so users can access certain engine functionality        */
            /* Mainly just pass through functions for the different manager's functions. */
            /*                                                                           */
            /*****************************************************************************/
            
            /**
             * @brief Queries the window for a key press.
             * 
             * @param key The keyboard key code being queried.
             * @return True if the key has been pressed.
             * @return False if the key was not pressed or released.
             */
            bool queryInput(input_code key);

            /**
             * @brief Loads a sound effect into the engine. 
             *        If sound doesn't play, loading failed.
             *        If the sound already exists in the engine,
             *        loading is skipped.
             * 
             * @param name The desired name of the sound effect.
             * @param path The path to the sound file.
             */
            void loadSound(const std::string& name, const std::string& path);

            /**
             * @brief Plays a sound effect.
             * 
             * @param name The designated name of the sound effect.
             */
            void playSound(const std::string& name);

            /**
             * @brief Removes a sound effect.
             * 
             * @param name The designated name of the sound effect.
             */
            void closeSound(const std::string& name);

            /**
             * @brief Removes all sound effects.
             * 
             */
            void clearAllSounds();

            /**
             * @brief Constructs a file path starting at the
             *        engine's "assets" directory. This is necessary
             *        since the engine will look for files to load
             *        starting from the "assets" directory.
             * 
             * @param path The path to the file inside the assets directory.
             * @return The full path name starting from assets directory. 
             */
            std::string filePath(const std::string& path);

            /**
             * @brief Loads an image file to be used as a sprite image.
             * 
             * @param name The desired name for the sprite image.
             * @param path The path to the image file.
             * @return True if the image file was successfully loaded.
             * @return False otherwise. 
             */
            bool loadSpriteImage(const std::string& name, const std::string& path);

            /**
             * @brief Removes a sprite image.
             * 
             * @param name The designated name for the image file.
             */
            void destroySpriteImage(const std::string& name);

            /**
             * @brief Removes all sprite images.
             * 
             */
            void clearAllImages();

            /**
             * @brief Create a new entity.
             * 
             * @return The designated entity ID for the new entity.
             *         The user should store these to access the
             *         created entities. There is no other way
             *         to get an entity's ID.
             */
            EntityID createEntity();

            /**
             * @brief Removes an entity and all related components.
             * 
             * @param e The entity ID of the desired entity.
             */
            void destroyEntity(EntityID e);

            /**
             * @brief Get a component assigned to an entity.
             * 
             * @tparam T The data type of the desired component.
             * @param e The entity ID of the desired entity.
             * @return A reference to the desired component.
             */
            template< typename T > T& getComponent(EntityID e)
            {
                return ECSManager.Get<T>(e);
            }

            /**
             * @brief Iterates over all entities that contain a 
             *        particular component(s).
             * 
             * @tparam EntityComponents 
             * @param callback Can be used to pass custom code that
             *                 will execute on all entities with the
             *                 desired components.
             */
            template< typename EntityComponents > void forEach(const ForEachCallback& callback)
            {
                ECSManager.ForEach<EntityComponents>(callback);
            }

            /**
             * @brief Loads a Lua script into the engine.
             * 
             * @param name The desired name for the script.
             * @param path The path to the script.
             * @param run Specifies if we want to run the script immediately or not.
             * @return True if the script was successfully loaded.
             * @return False otherwise.
             */
            bool loadScript(const std::string& name, const std::string& path, bool run);

            /**
             * @brief Converts degrees to radians. The engine stores 
             *        angles in degrees, but many trig. functions in
             *        c++ require radians.
             * 
             * @param degrees The desired angle in degrees.
             * @return The angle converted to radians.
             */
            double radians(const float degrees);

            /**
             * @brief Converts degrees to radians. The engine stores 
             *        angles in degrees, but many trig. functions in
             *        c++ require radians.
             * 
             * @param degrees The Rotation component.
             * @return The angle converted to radians.
             */
            double radians(const Rotation degrees);
    };
}