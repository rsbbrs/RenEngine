#pragma once

#include "ECS.h"

using namespace RenEngine;

// Initializes the counter for unique entity IDs.
void ECS::ecsStartup()
{
    count = 0;
}

// Currently does nothing.
void ECS::ecsShutdown()
{

}

/****************************/
/*                          */
/* PRIVATE HELPER FUNCTIONS */
/*                          */
/****************************/

ComponentIndex ECS::GetNextIndex()
{
    static ComponentIndex index = -1; // Returns the sequence 0, 1, 2, … every time this is called.
    index += 1;
    return index;
}

/***************************/
/*                         */
/* PUBLIC FACING FUNCTIONS */
/*                         */
/***************************/

// Creates a new entity with a unique entity ID.
EntityID ECS::Create()
{
    return ++count;
}



// Destroys the entity by removing all components.
void ECS::Destroy( EntityID e ) 
{
    for( const auto& comps : m_components ) 
        comps->Drop( e ); 
}