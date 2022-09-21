#include "Engine.h"

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
    std::vector<Sprite> sprites;

    // Loading sprite.
    if(renEngine->loadSpriteImage("mySprite", renEngine->filePath("sprites\\mySprite.png")))
    {
        std::cout << "Successfully loaded mySprite.\n";
        // Creates a sprite called mySprite with position (1, 1), scale of 1 and z value of 1.
        sprites.push_back(Sprite
            {
                "mySprite",
                vec2(0, 0),
                50,
                1
            });
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

        // Draws loaded sprites.
        renEngine->draw(sprites);
    });

    delete renEngine;

    return 0;
}