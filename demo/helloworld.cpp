#include "Engine.h"

using namespace RenEngine;

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
    std::vector<Sprite> sprites;

    // Loading sprite.
    if(renEngine->loadSpriteImage("mySprite1", renEngine->filePath("sprites\\mySprite.png")))
    {
        std::cout << "Successfully loaded mySprite1.\n";
        // Creates a sprite called mySprite with position (1, 1), scale of 1 and z value of 1.
        sprites.push_back(Sprite
            {
                "mySprite1",
                vec2(0, 0),
                50,
                180.0,
                1
            });
    }

    if(renEngine->loadSpriteImage("mySprite2", renEngine->filePath("sprites\\mySprite.png")))
    {
        std::cout << "Successfully loaded mySprite2.\n";
        // Creates a sprite called mySprite with position (1, 1), scale of 1 and z value of 1.
        sprites.push_back(Sprite
            {
                "mySprite2",
                vec2(50, 50),
                20,
                180.0,
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

        procInput(sprites[0], renEngine);

        // Draws loaded sprites.
        renEngine->draw(sprites);
    });

    delete renEngine;

    return 0;
}