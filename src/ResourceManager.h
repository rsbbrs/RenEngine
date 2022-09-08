#pragma once

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
            std::filesystem::path resolvePath(std::string);
    };
}