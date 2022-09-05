#include <SoundManager.h>

using namespace RenEngine;

// Initializes the sound manager.
void SoundManager::smStartup()
{
    soundInstance.init();
}

// Shuts down the sound manager.
void SoundManager::smShutdown()
{
    soundInstance.deinit();
}

// Loads a sound into the sounds list.
void SoundManager::loadSound(const std::string& name, const std::string& path)
{
    soundsList[name].load((path.c_str()));
}

// Plays the sound.
void SoundManager::playSound(const std::string& name)
{
    soundInstance.play(soundsList[name]);
}