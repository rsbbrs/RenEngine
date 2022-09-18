#pragma once

#include <iostream>
#include <string>
#include "glm/glm.hpp"
// #include "spdlog/spdlog.h"

namespace RenEngine
{
    // Forward declarations.
    class Engine;
    class GraphicsManager;
    class InputManager;

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

    // Sprite data.
    typedef struct
    {

    } Sprite;

    //  Some common keyboard buttons for games
    enum input_code
    {
        unknown = -1,

        left_shift = 340,
        left_ctrl,
        left_alt,
        
        space = 32,

        num_0 = 48,
        num_2,
        num_3,
        num_4,
        num_5,
        num_6,
        f1 = 290,
        f2,
        f3,
        f4,

        w = 87,
        a = 65,
        s = 83,
        d = 68,

        escape = 256,
        enter,
        tab,
    };

    // Full featured vector types.
    typedef glm::vec2 vec2;
    typedef glm::vec3 vec3;
    typedef glm::vec4 vec4;
}