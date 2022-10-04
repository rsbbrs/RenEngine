#pragma once

#include "ScriptManager.h"

using namespace RenEngine;

// Starts up the Lua state with built-in libraries. 
void ScriptManager::scmStartup()
{
    lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::table);
}

// Currently does nothing.
void ScriptManager::scmShutDown()
{}

// Loads a script into the scripts manager.
// Stored in the unordered map under "name"
// NOTE: Need to figure out what the load_file function returns on failure.
bool ScriptManager::loadScript(const std::string& name, const std::string& path)
{
    scripts[name] = lua.load_file(path);
    return true;
}

// Returns a script in the scripts map.
sol::load_result& ScriptManager::getScript(const std::string& name)
{
    return scripts[name];
}