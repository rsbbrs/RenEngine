#pragma once

#include "Engine.h"
using namespace RenEngine;

static std::unique_ptr<Engine> mainGame = std::make_unique<Engine>("Main Game", 1600, 900, false);

void loadAssets()
{
    mainGame->getLuaEnv().set_function("getBoxCollider",
    [&](const EntityID e, vec2& min, vec2& max)
    {
        mainGame->getBoxCollider(e, min, max);
    });

    mainGame->getLuaEnv().set_function("hasCollided",
    [&] (const EntityID e1, const EntityID e2) -> bool
    {
        return mainGame->physicsManager.coll_det(e1, e2);
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

    mainGame->gameLoop([&](){});
    std::cout << "Finished\n";

    mainGame.reset();
    return 0;
}