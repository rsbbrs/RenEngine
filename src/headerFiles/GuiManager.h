#pragma once

#include "Types.h"

namespace RenEngine
{
    class GuiManager
    {
        private:

        public:
            void startup(GraphicsManager& manager);
            void shutdown();
            void draw();
    };
}