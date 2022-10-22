#pragma once

#include "Engine.h"
#include "ECS.h"
#include <cmath>
#include <algorithm>

using namespace RenEngine;

int main(int argc, const char* argv[])
{
    // Dynamic allocation for using default arguments in case none are provided.
    Engine* renEngine = new Engine("Asteroids Demo", 1200, 720, false);

    // Sprite vector.
    std::vector<EntityID> entities;

    // Setup script for lua.
    if(renEngine->loadScript("Setup", renEngine->filePath("sprites\\setup.lua")))
        std::cout << "Successfully loaded setup.lua\n";

    // Entities must be loaded in the order they're gonna be drawn in.
    // To show the background behind the spaceship sprite, load it
    // first. This is due to the way the image is drawn; the entities with
    // the lowest entity ID are drawn first.
    // Loading background.
    if(renEngine->loadSpriteImage("Space", renEngine->filePath("sprites\\space.png")))
    {
        std::cout << "Successfully loaded space.png.\n";

        entities.push_back(renEngine->createEntity());      // EntityID 1
        Sprite sprite;
        Position pos;
        Rotation rot;
        Scale scale;
        sprite.name = "Space";
        pos.x = 0;
        pos.y = 0;
        pos.z = 1;
        rot.angle = 180;
        scale.scale = 180;

        renEngine->getComponent<Sprite>(entities[2]) = sprite;
        renEngine->getComponent<Position>(entities[2]) = pos;
        renEngine->getComponent<Rotation>(entities[2]) = rot;
        renEngine->getComponent<Scale>(entities[2]) = scale;
    }  
    
    // Loading sprite.
    if(renEngine->loadSpriteImage("Spaceship", renEngine->filePath("sprites\\Spaceship.png")))
    {
        std::cout << "Successfully loaded Spaceship sprite.\n";
        // Creates a sprite called Spaceship with position (1, 1), scale of 1 and z value of 1.

        // Entity setup.
        entities.push_back(renEngine->createEntity());      // EntityID 2
        Sprite mySprite;
        Position pos;
        Rotation rot;
        Scale scale;
        Velocity v;
        mySprite.name = "Spaceship";
        pos.x = 0;
        pos.y = 0;
        pos.z = 1;
        rot.angle = 0;
        scale.scale = 20;
        v.x = v.y = 0;
        
        // Setting the entity's components.
        renEngine->getComponent<Sprite>(entities[0]) = mySprite;
        renEngine->getComponent<Position>(entities[0]) = pos;
        renEngine->getComponent<Rotation>(entities[0]) = rot;
        renEngine->getComponent<Scale>(entities[0]) = scale;
        renEngine->getComponent<Velocity>(entities[0]) = v;

        // Lua script loading for spaceship entity.
        auto scriptPath = renEngine->filePath("scripts\\spaceship.lua");
        if(renEngine->loadScript("Spaceship", scriptPath))
        {
            std::cout << "Successfully loaded Spaceship script.\n";

            Script newScript;
            newScript.name = "Spaceship";
            newScript.path = scriptPath;

            renEngine->getComponent<Script>(entities[0]) = newScript;
        }

        /*
        entities.push_back(renEngine->createEntity());      // EntityID 3
        Rotation mvRot;
        mvRot.angle = 0;
        renEngine->getComponent<Rotation>(entities[1]) = mvRot;
        */
    }

    // Initializes the game loop.
    renEngine->gameLoop([&]() {});

    delete renEngine;

    return 0;
}