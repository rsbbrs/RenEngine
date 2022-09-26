#include "SoundManager.h"

using namespace RenEngine;

// Initializes the sound manager.
void SoundManager::smStartup()
{
    soundInstance.init();
}

// Shuts down the sound manager.
// Clears the sound list completely.
void SoundManager::smShutdown()
{
    clearSoundsList();
    soundInstance.deinit();
}

// Loads a sound into the sounds list.
// If sound already exists, skip loading.
void SoundManager::loadSound(const std::string& name, const std::string& path)
{
    if(soundsList.count(name) == 0)
        soundsList[name].load((path.c_str()));
}

// Plays the sound.
void SoundManager::playSound(const std::string& name)
{
    soundInstance.play(soundsList[name]);
}

// Destroy a sound
void SoundManager::closeSound(const std::string& name)
{
    soundsList.erase(name);
}

// Clear sound list.
void SoundManager::clearSoundsList()
{
    soundsList.clear();
}