#pragma once

#include "Types.h"

class PrivateImpl;

namespace RenEngine
{
    class GraphicsManager
    {
        private: 
            PrivateImpl* pImpl;

            friend class InputManager;
            void *getWindow();

        public:
            GraphicsManager();
            void gmStartup(Configuration windowParamm);
            void gmShutdown();
            bool closeWindow();
            bool loadImage(const std::string& name, const std::string& path);
    };
}