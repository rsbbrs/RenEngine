#pragma once

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

#include "Types.h"

namespace RenEngine
{
    class ScriptManager
    {
        typedef sol::state Lua;

        private:
            // Lua environment variable.
            Lua lua;

            // Script container.
            std::unordered_map<std::string, sol::load_result> scripts;

            // Startup and shutdown functions.
            void scmStartup();
            void scmShutDown();

        public:
            // Loads Lua scripts into the engine.
            bool loadScript( const std::string& name, const std::string& path );

            // Returns a script function loaded into the manager.
            sol::load_result& getScript(const std::string& name);

    };
}