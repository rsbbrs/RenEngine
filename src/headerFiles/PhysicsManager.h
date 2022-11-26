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

            bool coll_det(const RigidBody& rb1, const RigidBody& rb2);
            
            void coll_resolve(  RigidBody& rb1, 
                                RigidBody& rb2, 
                                Position& p1, 
                                Position& p2, 
                                std::string name1, 
                                std::string name2, 
                                int scale1, 
                                int scale2, 
                                const float coe, 
                                GraphicsManager* gm);
                                
            void collision();
            void updatePhysics(const std::chrono::time_point<std::chrono::steady_clock> dt);
    };
}