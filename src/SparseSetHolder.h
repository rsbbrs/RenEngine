#pragma once

#include <unordered_map>
#include "Types.h"

namespace RenEngine
{
    class SparseSetHolder 
    {
        public:
            // A virtual destructor, since we store pointers to this superclass 
            // yet have subclasses with destructors that need to run.
            virtual ~SparseSetHolder() = default;
            virtual bool Has( EntityID ) const = 0;
            virtual void Drop( EntityID ) = 0;
    };

    // Subclasses are templated on the component type they hold.
    template< typename T > class SparseSet : public SparseSetHolder 
    {
        public:
            std::unordered_map< EntityID, T > data;
            SparseSet() {};
            ~SparseSet() {};
            bool Has( EntityID e ) const override { return data.count( e ) > 0; };
            void Drop( EntityID e ) override { data.erase( e ); };
    };
}