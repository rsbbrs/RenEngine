#include "Engine.h"
using namespace RenEngine;

Engine::Engine(int width, int height, const char *name, bool fullscreen)
{
    window.width = width;
    window.height = height;
    window.name = name;
    window.fullscreen = fullscreen;

    startup();
}

void Engine::startup()
{
    graphics.gmStartup(window);
}

void Engine::shutdown()
{
    graphics.gmShutdown();
}

void Engine::gameLoop()
{
    bool running = true;

    while(running)
    {
        // Do stuff.
    }

    shutdown();
}