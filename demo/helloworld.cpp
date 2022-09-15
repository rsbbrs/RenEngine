#include "Engine.h"

int main(int argc, const char* argv[])
{
    if(argc < 5)
    {
        std::cerr << "Error: Four arguments are needed to run the engine." << "\n";
        std::cerr << "Format: helloworld width height name fullscreen." << "\n";
        return -1;
    }
    
    // Starts the engine.
    RenEngine::Engine myEngine(atoi(argv[1]), atoi(argv[2]), argv[3], std::string(argv[4]).compare("true") == 0? true : false);

    myEngine.gameLoop([&]()
    {
        if(myEngine.queryInput(RenEngine::input_code::enter))
        {
            std::cout << "Keyboard input working.\n";
            myEngine.loadSound("Success", myEngine.filePath("sounds\\success.mp3"));
            myEngine.playSound("Success");
        }
    });

    return 0;
}