#pragma once

#include <vector>
#include <functional>
#include <queue>

#include "SparseSetHolder.h"
#include "Types.h"

namespace RenEngine
{
    typedef int ComponentIndex;
    typedef std::function<void( EntityID )> ForEachCallback;

    class ECS
    {
        private:
            EntityID count;
            std::vector< std::unique_ptr<SparseSetHolder> > m_components;

            // Will be used to store deleted IDs so we can recycle them
            // when we create another entity
            std::queue<EntityID> deletedID;

            /****************************/
            /*                          */
            /* PRIVATE HELPER FUNCTIONS */
            /*                          */
            /****************************/

            ComponentIndex GetNextIndex()
            {
                static ComponentIndex index = -1; // Returns the sequence 0, 1, 2, … every time this is called.
                index += 1;
                return index;
            }

            template< typename T > 
            ComponentIndex GetComponentIndex() 
            {
                static ComponentIndex index = GetNextIndex(); // Only calls GetNextIndex() the first time this function is called.
                return index;
            }

            template< typename T > 
            std::unordered_map< EntityID, T >& GetAppropriateSparseSet()
            {
                // Get the index for T’s SparseSet
                const ComponentIndex index = GetComponentIndex<T>();

                // If we haven’t seen it yet, it must be past the end.
                // Since component indices are shared by all ECS instances,
                // it could happen that index is more than one past the end.
                if( index >= m_components.size() ) { m_components.resize( index+1 ); }
                    assert( index < m_components.size() );

                // Create the actual sparse set if needed.
                if( m_components[ index ] == nullptr ) 
                    m_components[index] = std::make_unique< SparseSet<T> >();

                // It’s safe to cast the SparseSetHolder to its subclass and return the std::unordered_map< EntityID, T > inside.
                return static_cast< SparseSet<T>& >( *m_components[ index ] ).data;
            }

            // Returns true if the entity has all types.
            template < typename T, typename... Rest > 
            bool HasAll( EntityID entity ) 
            {
                bool result = true;

                // https://stackoverflow.com/questions/48405482/variadic-template-no-matching-function-for-call/48405556#48405556
                if constexpr (sizeof...(Rest) > 0) 
                { 
                    result = HasAll<Rest...>(entity); 
                }

                return result && GetAppropriateSparseSet<T>().count( entity ) > 0;
            }

        public:
            /***************************/
            /*                         */
            /* PUBLIC FACING FUNCTIONS */
            /*                         */
            /***************************/

            // Startup and shutdown functions.
            void startup();// { count = 0; };
            void shutdown() {};
            
            // Create and destroy entities.
            EntityID Create() { 
                static EntityID newID = 0;
                EntityID result = -1;

                // Check if we can recycle old id value
                if (deletedID.size() != 0)
                {
                    result = deletedID.front();
                    deletedID.pop();
                    return result;
                }

                result = newID;

                // After creation, increment for next entity
                ++newID;

                return result; 
            };
            void Destroy(EntityID e)
            {
                for( const auto& comps : m_components ) 
                    comps->Drop( e );
                //count--;
                deletedID.push(e);
            }

            // Get component from an entity.
            // Gets entity's components.
            template< typename T > 
            T& Get( EntityID entity ) 
            {
                return GetAppropriateSparseSet<T>()[ entity ];
            }

            // Iterate over all entities that have the specified components.
            template< typename EntityComponents, typename... MoreComponents > 
            void ForEach( const ForEachCallback& callback ) 
            {
                // Iterate over elements of the first container.
                auto& container = GetAppropriateSparseSet<EntityComponents>();
                for( const auto& [entity, value] : container ) 
                {
                    // We know it has the first component.
                    // Skip the entity if it doesn't have the remaining components.
                    // This `if constexpr` is evaluated at compile time. It is needed when AndAlsoTheseComponents is empty.
                    // https://stackoverflow.com/questions/48405482/variadic-template-no-matching-function-for-call/48405556#48405556
                    if constexpr (sizeof...(MoreComponents) > 0) 
                    {
                        if( !HasAll<MoreComponents...>( entity ) ) 
                        {
                            continue;
                        }
                    }
                    callback( entity );
                }
            }
    };
}