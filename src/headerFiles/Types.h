#pragma once

#include <iostream>
#include <string>
#include <complex>

#include "glm/glm.hpp"
// #include "spdlog/spdlog.h"

namespace RenEngine
{
    // Forward declarations.
    class Engine;
    class GraphicsManager;
    class InputManager;
    class SoundManager;
    class ResourceManager;
    class ECS;
    class ScriptManager;
    class PhysicsManager;

    // Entity ID
    typedef long EntityID;

    // Full featured vector types.
    typedef glm::vec2 vec2;
    typedef glm::vec3 vec3;
    typedef glm::vec4 vec4;

    // Global types.
    typedef struct
    {
        struct window_param
        {
            int width, height;
            const char *name;
            bool fullscreen;
        } window;

    } Configuration;

    // Basic components for the ECS.
    // More can be added, and even by the user.
    struct Position : public vec3 {};
    struct Rotation{ float angle; };
    struct Scale { int scale; };
    struct Health { double percent; };
    struct Script { std::string name; std::string path; };
    struct Sprite { std::string name; bool rigidBody = true; };
    struct RigidBody 
    {
        vec2 velocity;
        vec2 acceleration;
        vec2 gravity;
        vec2 force;
        float mass;
        bool trueRB = true;
        bool static_obj = false;

        // Min/max dimensions of the collider.
        vec2 min;
        vec2 max;
    };

    //  Some common keyboard buttons for games
    enum input_code
    {
        unknown = -1,

        left_shift = 340,
        left_ctrl,
        left_alt,
        
        space = 32,

        num_0 = 48,
        num_1,
        num_2,
        num_3,
        num_4,
        num_5,
        num_6,
        f1 = 290,
        f2,
        f3,
        f4,

        a = 65,
        d = 68,
        f = 70,
        r = 82,
        s,
        w = 87,

        right = 262,
        left,
        down,
        up,

        escape = 256,
        enter,
        tab,
    };
}