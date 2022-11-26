#pragma once

#include "Engine.h"
using namespace RenEngine;

int main(void)
{
    Engine* mainGame = new Engine("Main Gaime", 1600, 900, false);



    mainGame->gameLoop([&](){});
    return 0;
}