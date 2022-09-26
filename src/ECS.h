#pragma once

#include <vector>
#include <functional>

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
            std::vector< std::unique_ptr< SparseSetHolder > > m_components;

            template<typename T> ComponentIndex GetComponentIndex();

            ComponentIndex GetNextIndex();

            template< typename T > std::unordered_map< EntityID, T >& GetAppropriateSparseSet();

            template <typename T, typename... Rest> bool HasAll( EntityID entity );

        public:
            // Startup and shutdown functions.
            void ecsStartup();
            void ecsShutdown();
            
            // Create and destroy entities.
            EntityID Create();
            void Destroy(EntityID e);

            // Get component from an entity.
            template< typename T > T& Get( EntityID e );

            // Iterate over all entities that have the specified components.
            template<typename EntityComponents, typename... MoreComponents> void ForEach(const ForEachCallback& callback);
    };
}