#pragma once

#include <unordered_map>
#include "soloud.h"
#include "soloud_wav.h"
#include "Types.h"

namespace RenEngine
{
    class SoundManager
    {
        private:
            SoLoud::Soloud soundInstance;
            std::unordered_map<std::string, SoLoud::Wav> soundsList;

        public:
            void startup();
            void shutdown();

            void loadSound(const std::string& name, const std::string& path);
            void playSound(const std::string& name);
            void closeSound(const std::string& name);
            void clearSoundsList();

            // Extra features provided by soloud's Wav libraries
            void setLooping(const std::string& name, int value);
            void stopSound(const std::string& name);
            void setVolume(const std::string& name, float value);


    };
}