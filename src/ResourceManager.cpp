#include <ResourceManager.h>

using namespace RenEngine;

// Sets the path to the assets folder.
void ResourceManager::rmStartup()
{
    assetsPath = "./assets";
}

void ResourceManager::rmShutdown()
{
    // Does nothing currently.
}

// Simply returns the path unchanged currently.
// Will need to be improved later.
std::string ResourceManager::resolvePath(std::string relativePath)
{
    return (assetsPath / relativePath).string();
}