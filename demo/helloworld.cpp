#include <iostream>
#include "Engine.h"

int main(int argc, const char* argv[])
{
    if(argc < 5)
    {
        std::cerr << "Error: Four arguments are needed to run the engine." << "\n";
        std::cerr << "Format: helloworld width height name fullscreen." << "\n";
    }
    bool fullscreen = std::string(argv[4]).compare("true") ? true : false;
    RenEngine::Engine myEngine(atoi(argv[1]), atoi(argv[2]), argv[3], fullscreen);

    myEngine.gameLoop();

    return 0;
}