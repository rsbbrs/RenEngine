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
            void smStartup();
            void smShutdown();

            void loadSound(const std::string&, const std::string&);
            void playSound(const std::string&);
            void closeSound(const std::string&);
            void clearSoundsList();
    };
}