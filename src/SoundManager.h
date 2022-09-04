#pragma once

#include <Types.h>
#include <soloud.h>
#include <unordered_map>

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