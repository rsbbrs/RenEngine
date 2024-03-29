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

            friend class InputManager; friend class GuiManager;
            void *getWindow();
            void createProjectionMatrix(glm::mat4& projection, int width, int height);
            void createTransformMatrix(const std::string name,
                                       const Position& pos, 
                                       const Rotation& rot, 
                                       const Scale& scale, 
                                       glm::mat4& transform);
        public:
            GraphicsManager();
            void startup(Configuration windowParam);
            void shutdown();
            bool closeWindow();

            // Sprite image handling functions.
            bool loadImage(const std::string& name, const std::string& path);
            void getBoxCollider(const std::string& name, const vec3 pos, const int scale, vec2& min, vec2& max);
            void destroyImage(const std::string& name);
            void clearAllImages();

            // Draw images.
            void draw(ECS& ecs, GuiManager& gm);
            
            // Getters for window dimensions.
            int width();
            int height();
    };
}