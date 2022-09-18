#pragma once

#include <vector>

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

            // Sprite image handling functions.
            bool loadImage(const std::string& name, const std::string& path);
            void destroyImage(const std::string& name);
            void clearAllImages();

            // Draw images.
            void draw(const std::vector<Sprite>& sprites);
    };
}