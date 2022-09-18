#pragma once

#include <string>
#include <filesystem>
#include "Types.h"

namespace RenEngine
{
    class ResourceManager
    {
        private:
            std::filesystem::path assetsPath;

        public:
            void rmStartup();
            void rmShutdown();
            std::string resolvePath(std::string relativePath);
    };
}