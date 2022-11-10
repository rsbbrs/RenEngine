#pragma once

#include "Types.h"

namespace RenEngine
{
    class PhysicsManager
    {
        private: 

        public: 
            startup();
            shutdown();

            void collisions();
            void updatePhysics();
            void getTime();
    }
}