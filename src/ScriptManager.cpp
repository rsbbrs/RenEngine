#pragma once

#include "ScriptManager.h"

using namespace RenEngine;

// Starts up the Lua state with built-in libraries.
// Creates callback functions to engine functionality
// so that Lua can access them.
void ScriptManager::scmStartup(GraphicsManager& graphicsManager, 
                               InputManager& inputManager, 
                               ResourceManager& resourceManager,
                               SoundManager& soundManager, 
                               ECS& ecsManager)
{
    scriptQuit = false;

    lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::table);
    lua.script("math.randomseed(0)");

    setInputCodes();

    // Input manager functions.
    lua.set_function("KeyPressed", [&](const input_code keycode) { return inputManager.keyPressed(graphicsManager, keycode); } );

    // Sound manager functions.
    lua.set_function("loadSound", [&](const std::string name, const std::string path) 
                                     { soundManager.loadSound(name, resourceManager.resolvePath(path)); } );
    lua.set_function("playSound", [&](const std::string name) { soundManager.playSound(name); } );
    lua.set_function("closeSound", [&](const std::string name) { soundManager.closeSound(name); } );
    lua.set_function("clearAllSounds", [&]() { soundManager.clearSoundsList(); } );

    // ECS manager functions.
    lua.set_function("createEntity", [&]() { ecsManager.Create(); } );
    lua.set_function("destroyEntity", [&](const EntityID e) { ecsManager.Destroy(e); } );

    // Quit function.
    lua.set_function("quit", [&]() { quit(); } );
}

void ScriptManager::setInputCodes()
{
    typedef std::initializer_list<std::pair<sol::string_view, input_code>> LuaKeyEnum;

    // Input keys enum sent to Lua.
    // Uses initializer list for input_code struct.
    LuaKeyEnum inputList = { 
        {"unknown", input_code::unknown},
        {"left_shift", input_code::left_shift},
        {"left_ctrl", input_code::left_ctrl},
        {"left_alt", input_code::left_alt},
        {"space", input_code::space},
        {"num_0", input_code::num_0},
        {"num_1", input_code::num_1},
        {"num_2", input_code::num_2},
        {"num_3", input_code::num_3},
        {"num_4", input_code::num_4},
        {"num_5", input_code::num_5},
        {"num_6", input_code::num_6},
        {"f1", input_code::f1},
        {"f2", input_code::f2},
        {"f3", input_code::f3},
        {"f4", input_code::f4},
        {"w", input_code::w},
        {"a", input_code::a},
        {"s", input_code::s},
        {"d", input_code::d},
        {"right", input_code::right},
        {"left", input_code::left},
        {"up", input_code::up},
        {"down", input_code::down},
        {"escape", input_code::escape},
        {"enter", input_code::enter},
        {"tab", input_code::tab},
    }; 
    lua.new_enum<input_code>("input_code", inputList);
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

// Quits the engine from script.
void ScriptManager::quit()
{
    scriptQuit = true;
}