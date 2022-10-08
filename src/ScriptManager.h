#pragma once

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

#include "Types.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "ECS.h"

namespace RenEngine
{
    class ScriptManager
    {
        private:
            typedef sol::state Lua;

            // Lua environment variable.
            Lua lua;

            // Script container.
            std::unordered_map<std::string, sol::load_result> scripts;

            // Helper functions for initialization.
            void setInputCodes();
            void setComponentStructs();

            // Script command to quit the engine.
            void quit();

        public:
            bool scriptQuit;

            // Startup and shutdown functions.
            void scmStartup(GraphicsManager& graphicsManager,
                            InputManager& inputManager, 
                            ResourceManager& resourceManager,
                            SoundManager& soundManager,
                            ECS& ecsManager);
            void scmShutDown();

            // Loads Lua scripts into the engine.
            bool loadScript( const std::string& name, const std::string& path );

            // Returns a script function loaded into the manager.
            sol::load_result& getScript(const std::string& name);

            // Runs all entities with script components.
            void update(ECS& ecsManager);
    };
}