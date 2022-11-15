#pragma once

#include "Engine.h"

using namespace RenEngine;

int main()
{
    Engine* physDemo = new Engine("Physics Demo");

    if(physDemo->loadScript("Setup", physDemo->filePath("scripts\\physDemoSetup.lua"), true))
        std::cout << "Successfully loaded physDemoSetup.lua\n";
    else
        std::cout << "Failed to load physDemoSetup.lua\n";

    RigidBody& rb = physDemo->getComponent<RigidBody>(1);
    physDemo->getBoxCollider(1, rb.min, rb.max);

    // Runs the game loop.
    physDemo->gameLoop([&](){});

    delete physDemo;

    return 0; 
}