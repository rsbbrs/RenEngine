#pragma once

#include "Types.h"
#include <algorithm>
#include <chrono>

namespace RenEngine
{
    class PhysicsManager
    {
        private:
            std::chrono::time_point<std::chrono::steady_clock> start;
            ECS* ecs;
            GraphicsManager* gm;

        public: 
            void startup(ECS* ecs, GraphicsManager* gm);
            void shutdown();

            void collision();
            void updatePhysics(const std::chrono::time_point<std::chrono::steady_clock> dt);
    };
}