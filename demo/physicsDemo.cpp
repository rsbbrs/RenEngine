#pragma once

#include "Engine.h"

using namespace RenEngine;

int main()
{
    Engine* physDemo = new Engine("Physics Demo", 1600, 900, false);

    if(physDemo->loadScript("Setup", physDemo->filePath("scripts\\physDemoSetup.lua"), true))
        std::cout << "Successfully loaded physDemoSetup.lua\n";
    else
        std::cout << "Failed to load physDemoSetup.lua\n";

    RigidBody& rb1 = physDemo->getComponent<RigidBody>(1);
    physDemo->getBoxCollider(1, rb1.min, rb1.max);

    RigidBody& rb2 = physDemo->getComponent<RigidBody>(2);
    physDemo->getBoxCollider(2, rb2.min, rb2.max);

    // Runs the game loop.
    physDemo->gameLoop([&](){});

    delete physDemo;

    return 0; 
}