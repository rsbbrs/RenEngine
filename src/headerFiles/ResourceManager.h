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
            void startup();
            void shutdown();
            std::string resolvePath(std::string relativePath);
    };
}