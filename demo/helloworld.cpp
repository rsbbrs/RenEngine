#include "Engine.h"
#include "ECS.h"

using namespace RenEngine;

void procInput(EntityID id, Engine* engine)
{
    Position& pos = engine->getComponent<Position>(id);
    Rotation& rot = engine->getComponent<Rotation>(id);
    Scale& scale = engine->getComponent<Scale>(id);

    if(engine->queryInput(input_code::up))
        scale.scale != 100 ? scale.scale += 1 : scale.scale = 100;

    if(engine->queryInput(input_code::down))
        scale.scale != 0 ? scale.scale -= 1 : scale.scale = 0;

    if(engine->queryInput(input_code::w))
        pos.y += 1;

    if(engine->queryInput(input_code::a))
        pos.x -= 1;

    if(engine->queryInput(input_code::s))
        pos.y -= 1;

    if(engine->queryInput(input_code::d))
        pos.x += 1;

    if(engine->queryInput(input_code::left))
        rot.angle += 1.0;

    if(engine->queryInput(input_code::right))
        rot.angle -= 1.0;
}

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
    if(renEngine->loadSpriteImage("mySprite", renEngine->filePath("sprites\\mySprite.png")))
    {
        std::cout << "Successfully loaded mySprite.\n";
        // Creates a sprite called mySprite with position (1, 1), scale of 1 and z value of 1.

        // Entity setup.
        entities.push_back(newEntity);
        Sprite mySprite;
        Position pos;
        Rotation rot;
        Scale scale;
        mySprite.name = "mySprite";
        pos.x = 0;
        pos.y = 0;
        pos.z = 1;
        rot.angle = 180;
        scale.scale = 50;
        
        // Setting the entity's components.
        renEngine->getComponent<Sprite>(entities[0]) = mySprite;
        renEngine->getComponent<Position>(entities[0]) = pos;
        renEngine->getComponent<Rotation>(entities[0]) = rot;
        renEngine->getComponent<Scale>(entities[0]) = scale;
    }

    if(renEngine->loadScript("myScript", renEngine->filePath("scripts\\myScript.lua")))
    {
        std::cout << "Successfully loaded myScript.\n";

        Script newScript;
        newScript.name = "myScript";

        renEngine->getComponent<Script>(entities[0]) = newScript;


    }

    // Callback for the engine.
    renEngine->gameLoop([&]()
    {
        // Checks if user input is pressed to play the sound.
        if(renEngine->queryInput(input_code::enter))
        {
            renEngine->loadSound("Success", renEngine->filePath("sounds\\success.mp3"));
            renEngine->playSound("Success");
        }

        procInput(entities[0], renEngine);
    });

    delete renEngine;

    return 0;
}