#pragma once

#include <Types.h>
#include <unordered_map>
#include "soloud.h"
#include "soloud_wav.h"

namespace RenEngine
{
    class SoundManager
    {
        private:
            SoLoud::Soloud soundInstance;
            std::unordered_map<string, SoLoud::Wav> soundsList;

        public:
            void smStartup();
            void smShutdown();

            void loadSound(const string&, const string&)
    };
}