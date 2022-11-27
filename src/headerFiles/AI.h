#pragma once

#include "Types.h"
#include "ECS.h"
#include <functional>

namespace RenEngine
{
    // The idea for this class is that the user can
    // create it and pass the entity ID of the object
    // that will contain some kind of AI.
    // Then, they can use the callback function to
    // implement any kind of AI algorithms needed.
    // Will it work?, we'll see...
    class AI
    {
        private:
            typedef std::function<void()> AICallback;

            // Useful to track various components of the AI.
            EntityID myID;

            // Other parts of AI state can go here if necessary.

        public:
            AI(const EntityID e) : myID(e) {}
            // The user can specify his desired AI algorithm
            // in here as part of the callback function.
            // In our case, we can write the state machine
            // in here. The only thing we have to define
            // is what state we're using.
            void checkState(const AICallback& callback);
    };
}