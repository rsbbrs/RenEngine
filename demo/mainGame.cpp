#pragma once

#include "Engine.h"
using namespace RenEngine;

static std::unique_ptr<Engine> mainGame = std::make_unique<Engine>("Main Game", 1600, 900, false);

void loadAssets()
{
    mainGame->scriptManager.lua.set_function("getBoxCollider",
    [&](const EntityID e, vec2& min, vec2& max)
    {
        mainGame->getBoxCollider(e, min, max);
    });

    if(mainGame->loadScript("LoadAssets", 
        mainGame->filePath("scripts/main/loadAssets.lua"), true))
        {
            std::cout << "Assets successfully loaded" << std::endl;
        }
        else
        {
            std::cout << "Assets failed to load" << std::endl;
        }
}

int main(void)
{
    loadAssets();

    mainGame->gameLoop([&](){ 
        // State machine?
    });
    
    return 0;
}