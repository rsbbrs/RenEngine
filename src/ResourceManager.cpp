#include <ResourceManager.h>

using namespace RenEngine;

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
std::filesystem::path ResourceManager::resolvePath(std::string relativePath)
{
    return assetsPath / relativePath;
}