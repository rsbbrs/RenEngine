#include "Engine.h"
#include "ECS.h"

using namespace RenEngine;

int main(int argc, const char* argv[])
{
    // Dynamic allocation for using default arguments in case none are provided.
    Engine* renEngine;

    // Starts the engine with default or user specified arguments.
    if(argc < 5)
    {
        std::cerr << "Note: Four arguments can be passed to the engine. Starting with default arguments" << "\n";
        std::cerr << "Format: helloworld name width height fullscreen." << "\n\n";
        renEngine = new Engine();
    }
    else
    {
        renEngine = new Engine(argv[1], atoi(argv[2]), atoi(argv[3]), std::string(argv[4]).compare("true") == 0? true : false);
    }

    // Sprite vector.
    std::vector<EntityID> entities;
    EntityID newEntity = renEngine->createEntity();
    
    // Loading sprite.
    if(renEngine->loadSpriteImage("Spaceship", renEngine->filePath("sprites\\Spaceship.png")))
    {
        std::cout << "Successfully loaded Spaceship sprite.\n";
        // Creates a sprite called Spaceship with position (1, 1), scale of 1 and z value of 1.

        // Entity setup.
        entities.push_back(newEntity);
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
        scale.scale = 25;
        v.x = v.y = 0;
        
        // Setting the entity's components.
        renEngine->getComponent<Sprite>(entities[0]) = mySprite;
        renEngine->getComponent<Position>(entities[0]) = pos;
        renEngine->getComponent<Rotation>(entities[0]) = rot;
        renEngine->getComponent<Scale>(entities[0]) = scale;
        renEngine->getComponent<Velocity>(entities[0]) = v;
    }
    auto scriptPath = renEngine->filePath("scripts\\myScript.lua");

    if(renEngine->loadScript("Spaceship", scriptPath))
    {
        std::cout << "Successfully loaded Spaceship script.\n";

        Script newScript;
        newScript.name = "Spaceship";
        newScript.path = scriptPath;

        renEngine->getComponent<Script>(entities[0]) = newScript;
    }

    // Initializes the game loop.
    renEngine->gameLoop([&]()
    {

    });

    delete renEngine;

    return 0;
}