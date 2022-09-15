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
            void gmStartup(Configuration);
            void gmShutdown();
            bool closeWindow();
    };
}