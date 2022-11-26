#pragma once

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

#include "Types.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "PhysicsManager.h"
#include "ECS.h"

namespace RenEngine
{
    class ScriptManager
    {
        private:
            typedef sol::state Lua;



            // Script container.
            std::unordered_map<std::string, sol::load_result> scripts;

            // Helper functions for initialization.
            void setInputCodes();
            void setComponentStructs();

            // Script command to quit the engine.
            void quit();

        public:
            bool scriptQuit;
            // Lua environment variable.
            Lua lua;

            // Startup and shutdown functions.
            void startup(GraphicsManager& graphicsManager,
                            InputManager& inputManager, 
                            ResourceManager& resourceManager,
                            SoundManager& soundManager,
                            ECS& ecsManager);
            void shutDown();

            // Loads Lua scripts into the engine.
            bool loadScript(const std::string& name, const std::string& path, bool run);

            // Returns a script function loaded into the manager.
            sol::load_result& getScript(const std::string& name);

            // Runs all entities with script components.
            void update(ECS& ecsManager);
    };
}