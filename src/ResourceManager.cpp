#pragma once

#include "ResourceManager.h"

using namespace RenEngine;

// Sets the path to the assets folder.
void ResourceManager::startup()
{
    assetsPath = ".\\assets";
}

void ResourceManager::shutdown()
{
    // Does nothing currently.
}

// Returns a path starting from assets directory.
std::string ResourceManager::resolvePath(std::string relativePath)
{
    return (assetsPath / relativePath).string();
}