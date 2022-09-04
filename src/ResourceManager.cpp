#include <ResourceManager.h>

using namespace RenEngine;

void ResourceManager::rmStartup()
{
    // Does nothing currently.
}

void ResourceManager::rmShutdown()
{
    // Does nothing currently.
}

// Simply returns the path unchanged currently.
// Will need to be improved later.
std::string ResourceManager::resolvePath(std::string relativePath)
{
    return relativePath;
}