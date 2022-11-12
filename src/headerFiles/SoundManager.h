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
    };
}