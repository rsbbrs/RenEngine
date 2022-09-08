#pragma once

#include <types.h>
#include <string>
#include <filesystem>

namespace RenEngine
{
    class ResourceManager
    {
        private:
            std::filesystem::path assetsPath;

        public:
            void rmStartup();
            void rmShutdown();
            std::string resolvePath(std::string);
    };
}