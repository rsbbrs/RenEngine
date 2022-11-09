#pragma once

#include "Engine.h"
#include <cmath>
#include <string>

using namespace RenEngine;

int main(int argc, const char* argv[])
{
    // Dynamic allocation for using default arguments in case none are provided.
    Engine* renEngine = new Engine("Engine Demo", 1200, 720, false);

    // Sprite vector.
    EntityID background, spaceship;

    // Setup script for lua.
    if(renEngine->loadScript("Setup", renEngine->filePath("sprites\\setup.lua"), true))
        std::cout << "Successfully loaded setup.lua\n";

    // Entities must be loaded in the order they're gonna be drawn in.
    // To show the background behind the spaceship sprite, load it
    // first. This is due to the way the image is drawn; the entities with
    // the lowest entity ID are drawn first.
    // Loading background.
    if(renEngine->loadSpriteImage("Space", renEngine->filePath("sprites\\space.png")))
    {
        std::cout << "Successfully loaded space.png.\n";

        background = renEngine->createEntity();      // EntityID 1
        Sprite sprite;
        Position pos;
        Rotation rot;
        Scale scale;
        sprite.name = "Space";
        pos.x = 0.0;
        pos.y = 0.0;
        pos.z = 1.0;
        rot.angle = 180;
        scale.scale = 180;

        renEngine->getComponent<Sprite>(background) = sprite;
        renEngine->getComponent<Position>(background) = pos;
        renEngine->getComponent<Rotation>(background) = rot;
        renEngine->getComponent<Scale>(background) = scale;
    }
    
    // Loading sprite.
    if(renEngine->loadSpriteImage("Spaceship", renEngine->filePath("sprites\\Spaceship.png")))
    {
        std::cout << "Successfully loaded Spaceship.png.\n";
        // Creates a sprite called Spaceship with position (1, 1), scale of 1 and z value of 1.

        // Entity setup.
        spaceship = renEngine->createEntity();      // EntityID 2
        Sprite mySprite;
        Position pos;
        Rotation rot;
        Scale scale;
        RigidBody rb;
        mySprite.name = "Spaceship";
        pos.x = 0.0;
        pos.y = 0.0;
        pos.z = 1.0;
        rot.angle = 0;
        scale.scale = 20;
        rb.velocity.x = rb.velocity.y = 0;
        rb.mass = 50;
        
        // Setting the entity's components.
        renEngine->getComponent<Sprite>(spaceship) = mySprite;
        renEngine->getComponent<Position>(spaceship) = pos;
        renEngine->getComponent<Rotation>(spaceship) = rot;
        renEngine->getComponent<Scale>(spaceship) = scale;
        renEngine->getComponent<RigidBody>(spaceship) = rb;

        // Lua script loading for spaceship entity.
        auto scriptPath = renEngine->filePath("scripts\\spaceship.lua");
        if(renEngine->loadScript("Spaceship", scriptPath, false))
        {
            std::cout << "Successfully loaded spaceship.lua.\n";

            Script newScript;
            newScript.name = "Spaceship";
            newScript.path = scriptPath;

            renEngine->getComponent<Script>(spaceship) = newScript;
        }
    }

    /* Loads the lazer image and sound effect to the engine.
    if(renEngine->loadSpriteImage("Laser", renEngine->filePath("sprites\\laser.png")))
    {
        std::cout << "Successfully loaded laser.png\n";
        //renEngine->loadSound("Gunshot", renEngine->filePath("sounds\\gunshot.mp3"));
    }*/

    int laserSpeed = 8;
    bool wasPressed = false;
    
    // Initializes the game loop.
    renEngine->gameLoop([&]() 
    {
        // Creates the laser entity when the player fires the spaceship's cannon.
        if(renEngine->queryInput(input_code::space) && !wasPressed)
        {
            renEngine->playSound("Gunshot");
            wasPressed = true;
            EntityID newID = renEngine->createEntity();

            Sprite laser = {"Laser"};
            Scale scale = {10};
            Rotation angle = {renEngine->getComponent<Rotation>(spaceship).angle + 90};
            Position pos = renEngine->getComponent<Position>(spaceship);

            renEngine->getComponent<Sprite>(newID) = laser;
            renEngine->getComponent<Position>(newID) = pos;
            renEngine->getComponent<Scale>(newID) = scale;
            renEngine->getComponent<Rotation>(newID) = angle;
        }

        // Resets the button press if the button was released.
        if(!renEngine->queryInput(input_code::space))
            wasPressed = false;

        // Updates laser components' positions after they've been fired.
        renEngine->forEach<Sprite>([&](EntityID e)
        {
            if(renEngine->getComponent<Sprite>(e).name == "Laser")
            {
                Position& pos = renEngine->getComponent<Position>(e);
                Rotation angle = renEngine->getComponent<Rotation>(e);

                if(pos.x < -185 || pos.x > 185 || pos.y < -121 || pos.y > 121)
                    renEngine->destroyEntity(e);
                else
                {
                    pos.x += (float)cos(renEngine->radians(angle)) * laserSpeed;
                    pos.y += (float)sin(renEngine->radians(angle)) * laserSpeed;
                }                
            }
        });
    });

    delete renEngine;

    return 0;
}