#pragma once

#include <Types.h>

class PrivateImpl;

namespace RenEngine
{
    class GraphicsManager
    {
        private: 
            PrivateImpl* pimpl;

            friend class InputManager;
            void *getWindow();

        public:
            GraphicsManager();
            void gmStartup(Configuration);
            void gmShutdown();
            bool closeWindow();
    };
}