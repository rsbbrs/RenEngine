#pragma once

#include "Types.h"
#include <chrono>

namespace RenEngine
{
    class PhysicsManager
    {
        private:
            std::chrono::time_point<std::chrono::steady_clock> start;
            ECS* manager;

        public: 
            void startup(ECS* manager);
            void shutdown();

            void collisionDetection();
            void collisionResolution();
            void updatePhysics(const std::chrono::time_point<std::chrono::steady_clock> dt);
    };
}