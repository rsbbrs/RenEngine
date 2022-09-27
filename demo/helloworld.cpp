#include "Engine.h"

using namespace RenEngine;

/*

void procInput(Sprite& sprites, Engine* engine)
{
        if(engine->queryInput(input_code::up))
            sprites.scale != 100 ? sprites.scale += 1 : sprites.scale = 100;

        if(engine->queryInput(input_code::down))
            sprites.scale != 0 ? sprites.scale -= 1 : sprites.scale = 0;

        if(engine->queryInput(input_code::w))
            sprites.position.y += 1;

        if(engine->queryInput(input_code::a))
            sprites.position.x -= 1;

        if(engine->queryInput(input_code::s))
            sprites.position.y -= 1;

        if(engine->queryInput(input_code::d))
            sprites.position.x += 1;

        if(engine->queryInput(input_code::left))
            sprites.rotate += 1.0;

        if(engine->queryInput(input_code::right))
            sprites.rotate -= 1.0;
}*/

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

    // Loading sprite.
    if(renEngine->loadSpriteImage("mySprite", renEngine->filePath("sprites\\mySprite.png")))
    {
        std::cout << "Successfully loaded mySprite.\n";
        // Creates a sprite called mySprite with position (1, 1), scale of 1 and z value of 1.
        entities.push_back(renEngine->createEntity());
        Position pos = renEngine->getComponent<Position>(entities[0]);
        Scale scale = renEngine->getComponent<Scale>(entities[0]);
        pos.x = 0;
        pos.y = 0;
        pos.z = 1;
        scale.scale = 50;
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
    });

    delete renEngine;

    return 0;
}