#pragma once

#include <Engine.h>

using namespace RenEngine;

// Constructor.
Engine::Engine(int width, int height, const char *name, bool fullscreen)
: total_loop_time(1.f/120.f)
{
    config.window.width = width;
    config.window.height = height;
    config.window.name = name;
    config.window.fullscreen = fullscreen;

    startup();
}

// Starts up all managers.
void Engine::startup()
{
    graphicsManager.gmStartup(config);
    inputManager.imStartup();
    resourceManager.rmStartup();
    soundManager.smStartup();
}

// Shuts down the managers.
void Engine::shutdown()
{
    soundManager.smShutdown();
    resourceManager.rmShutdown();
    inputManager.imShutdown();
    graphicsManager.gmShutdown();
}

// Main game loop where game logic will be processed.
// Runs 60 times per second.
void Engine::gameLoop(const UpdateCallback& callback)
{
    // Variables used for timing statistics.
    int loops = 0;
    const auto start = time(0);

    // Game loop. According to my calculations, the loop runs
    // approx 60 lps by making the calculation subtract from
    // 1/120 of a second. I did this due to a comment on the
    // discord my Cameron Massey stating that the Windows's sleep
    // function doubles the amount of time to sleep. Halfving
    // the interval per loop seems to make it run in 1/60 of
    // a second.
    while(graphicsManager.closeWindow() && !inputManager.keyPressed(graphicsManager, input_code::escape))
    {
        // Tick start.
        const auto t1 = std::chrono::steady_clock::now();

        // Update input state.
        inputManager.update();

        // User callback to specify custom behaviour.
        callback();
       
        loops++;

        //Tick end.
        const auto t2 = std::chrono::steady_clock::now();

        // Send engine to sleep after the tick.
        // The time spent sleeping will be 1/60 - (tick_end - tick_start).
        std::this_thread::sleep_for(total_loop_time - (t2 - t1));
    }

    // Statistics for loop timing printed after game loop finishes.
    const auto end = time(0) - start;
    std::cout << "Game loop terminated.\nTotal time running: " << end << " seconds.\n"
              << "Total loops: " << loops << "\nLoops per second: " << (double)loops / (double)end << "\n";

    shutdown();
}

/**************************************************/
/*                                                */
/*  API function implementations for the engine.  */
/*                                                */
/**************************************************/
bool Engine::queryInput(input_code key)
{
    return inputManager.keyPressed(graphicsManager, key);
}

void Engine::loadSound(const std::string& name, const std::string& path)
{
    soundManager.loadSound(name, path);
}

void Engine::playSound(const std::string& name)
{
    soundManager.playSound(name);
}

void Engine::closeSound(const std::string& name)
{
    soundManager.closeSound(name);
}

void Engine::clearAllSounds()
{
    soundManager.clearSoundsList();
}

std::string Engine::filePath(const std::string& path)
{
    return resourceManager.resolvePath(path);
}

bool Engine::loadSpriteImage(const std::string& name, const std::string& path)
{
    return graphicsManager.loadImage(name, path);
}

void Engine::destroySpriteImage(const std::string& name)
{
    graphicsManager.destroyImage(name);
}

void Engine::clearAllImages()
{
    graphicsManager.clearAllImages();
}

void Engine::draw(const std::vector<Sprite>& sprites)
{
    graphicsManager.draw(sprites);
}
