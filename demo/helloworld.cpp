#include "Engine.h"

using namespace RenEngine;

int main(int argc, const char* argv[])
{
    if(argc < 5)
    {
        std::cerr << "Error: Four arguments are needed to run the engine." << "\n";
        std::cerr << "Format: helloworld width height name fullscreen." << "\n";
        return -1;
    }
    
    // Starts the engine.
    Engine renEngine(argv[1], atoi(argv[2]), atoi(argv[3]), std::string(argv[4]).compare("true") == 0? true : false);

    // Sprite vector.
    std::vector<Sprite> sprites;
    if(renEngine.loadSpriteImage("mySprite", renEngine.filePath("sprites\\mySprite.png")))
    {
        std::cout << "Successfully loaded mySprite.\n";
        // Creates a sprite called mySprite with position (1, 1), scale of 1 and z value of 1.
        sprites.push_back(Sprite
            {
                "mySprite",
                vec2(600, 340),
                1,
                1
            });
    }

    // Callback for the engine.
    renEngine.gameLoop([&]()
    {
        // Checks if user input is pressed to play the sound.
        if(renEngine.queryInput(input_code::enter))
        {
            renEngine.loadSound("Success", renEngine.filePath("sounds\\success.mp3"));
            renEngine.playSound("Success");
        }

        // Draws loaded sprites.
        renEngine.draw(sprites);
    });

    return 0;
}