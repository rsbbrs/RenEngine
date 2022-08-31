#include <iostream>
#include "Engine.h"

int main(int argc, const char* argv[])
{
    bool fullscreen = std::string(argv[4]).compare("true") ? true : false;
    RenEngine::Engine::Engine(atoi(argv[1]), atoi(argv[2]), argv[3], fullscreen);

    return 0;
}