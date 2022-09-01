#include "Engine.h"
using namespace RenEngine;

// Constructor.
Engine::Engine(int width, int height, const char *name, bool fullscreen)
: one_sixtieth_of_a_second(1.f/60.f)
{
    window.width = width;
    window.height = height;
    window.name = name;
    window.fullscreen = fullscreen;

    startup();
}

// Starts up all managers.
void Engine::startup()
{
    graphics.gmStartup(window);
}

// Shuts down the managers.
void Engine::shutdown()
{
    graphics.gmShutdown();
}

// Main game loop where game logic will be processed.
// Runs 60 times per second.
void Engine::gameLoop()
{
    bool running = true;
    int loops = 0;

    const auto start = time(0);

    // Game loop. Currently not running at 60 lps, more like 30 lps.
    while(running)
    {
        // Tick start.
        const auto t1 = std::chrono::steady_clock::now();

        // Do stuff.
        //Currently just counting loops
        if(loops == 600)
            break;
        
        loops++;

        //Tick end.
        const auto t2 = std::chrono::steady_clock::now();

        // Send engine to sleep after the tick.
        // The time spent sleeping will be 1/60 - (tick_end - tick_start).
        std::this_thread::sleep_for(one_sixtieth_of_a_second - (t2 - t1));
    }
    const auto end = time(0) - start;
    std::cout << "Game loop terminated.\nTotal time running: " << end << " seconds.\n"
              << "Total loops: " << loops << "\nLoops per second: " << (double)loops / (double)end << "\n";

    shutdown();
}