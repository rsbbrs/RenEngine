#pragma once

#include <string>

namespace RenEngine
{
    // Forward declarations.
    class Engine;
    class GraphicsManager;
    class InputManager;

    // Global types.
    typedef struct window_param
    {
        int width, height;
        const char *name;
        bool fullscreen;
    } Window;
}