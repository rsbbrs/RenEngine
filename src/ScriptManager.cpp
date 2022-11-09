#pragma once

#include "ScriptManager.h"
#include <chrono>

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
    setComponentStructs();

    // Graphics manager functions.
    lua.set_function("loadImage", [&](const std::string& name, const std::string path) 
    {
        return graphicsManager.loadImage(name, resourceManager.resolvePath(path));
    });
    lua.set_function("destroyImage", [&](const std::string& name) { graphicsManager.destroyImage(name); } );
    lua.set_function("closeAllImages", [&]() { graphicsManager.clearAllImages(); });
    lua.set_function("winWidth", [&]() { return graphicsManager.width(); } );
    lua.set_function("winHeight", [&]() { return graphicsManager.height(); } );


    // Input manager functions.
    lua.set_function("keyPressed", [&](const input_code keycode) { return inputManager.keyPressed(graphicsManager, keycode); } );

    // Sound manager functions.
    lua.set_function("loadSound", [&](const std::string name, const std::string path) 
    {
        soundManager.loadSound(name, resourceManager.resolvePath(path)); 
    });
    lua.set_function("playSound", [&](const std::string name) { soundManager.playSound(name); } );
    lua.set_function("closeSound", [&](const std::string name) { soundManager.closeSound(name); } );
    lua.set_function("clearAllSounds", [&]() { soundManager.clearSoundsList(); } );

    // ECS manager functions.
    lua.set_function("createEntity", [&]() { return ecsManager.Create(); } );
    lua.set_function("destroyEntity", [&](const EntityID e) { ecsManager.Destroy(e); } );

    // Component getters.
    lua.set_function("getPosition", [&](const EntityID e) -> Position& { return ecsManager.Get<Position>(e); } );
    lua.set_function("getRotation", [&](const EntityID e) -> Rotation& { return ecsManager.Get<Rotation>(e); } );
    lua.set_function("getScale", [&](const EntityID e) -> Scale& { return ecsManager.Get<Scale>(e); } );
    lua.set_function("getRigidBody", [&](const EntityID e) -> RigidBody& { return ecsManager.Get<RigidBody>(e); } );
    lua.set_function("getHealth", [&](const EntityID e) -> Health& { return ecsManager.Get<Health>(e); } );
    lua.set_function("getScript", [&](const EntityID e) -> Script& { return ecsManager.Get<Script>(e); } );
    lua.set_function("getSprite", [&](const EntityID e) -> Sprite& { return ecsManager.Get<Sprite>(e); } );

    // Lua state in the engine.
    lua.set_function("getState", [&]() { return true; } );

    // Quit function.
    lua.set_function("quit", [&]() { quit(); } );

    //lua.set_function("getTime", [&]() { return std::chrono::steady_clock::now(); } );
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

// Initializes all component structures into Lua.
void ScriptManager::setComponentStructs()
{
    lua.new_usertype<Position>(
        "Position",
        sol::constructors<Position()>(),
        "x", &Position::x,
        "y", &Position::y
    );

    lua.new_usertype<Rotation>(
        "Rotation",
        sol::constructors<Rotation()>(),
        "angle", &Rotation::angle
    );

    lua.new_usertype<Scale>(
        "Scale",
        sol::constructors<Scale()>(),
        "scale", &Scale::scale
    );

    lua.new_usertype<Health>(
        "Health",
        sol::constructors<Health()>(),
        "percent", &Health::percent
    );

    lua.new_usertype<Script>(
        "Script",
        sol::constructors<Script()>(),
        "name", &Script::name,
        "path", &Script::path
    );

    lua.new_usertype<Sprite>(
        "Sprite",
        sol::constructors<Sprite()>(),
        "name", &Sprite::name
    );

    // Rigid body stuff.
    lua.new_usertype<vec2>(
        "vec2",
        sol::constructors<vec2()>(),
        "x", &vec2::x,
        "y", &vec2::y
    );

    lua.new_usertype<vec3>(
        "vec3",
        sol::constructors<vec3()>(),
        "x", &vec3::x,
        "y", &vec3::y,
        "Z", &vec3::z
    );

    lua.new_usertype<RigidBody>(
        "RigidBody",
        sol::constructors<RigidBody()>(),
        "velocity", &RigidBody::velocity,
        "acceleration", &RigidBody::acceleration,
        "gravity", &RigidBody::gravity,
        "force", &RigidBody::force,
        "mass", &RigidBody::mass
    );
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

// Runs the scripts attached to each entity.
void ScriptManager::update(ECS& manager)
{
    manager.ForEach<Script>([&](EntityID e)
    {
        Script& entity_script = manager.Get<Script>(e);
        loadScript(entity_script.name, entity_script.path);
        getScript(entity_script.name)();
    });
}