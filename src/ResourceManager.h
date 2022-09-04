#pragma once

#include <string>
#include <filesystem>

namespace RenEngine
{
    class ResourceManager
    {
        public:
            void rmStartup();
            void rmShutdown();
            std::string resolvePath(std::string);
    };
}