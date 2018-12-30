#pragma once

#include "sly/global.h"
#include "sly/collections/list.h"
#include "sly/pair.h"


    namespace sly {

    template <typename TKeyType, typename TItemType, typename TCollectionType = List<Pair<TKeyType, TItemType>>>
    class Map : public Collection<Pair<TKeyType, TItemType>>
    {
        private:

        public:
            Map();

            void add(const TKeyType key, const TItemType value);        
            void remove(const TKeyType key);
            
            TItemType get(const TKeyType key) const;
            void set(const TKeyType key, const TItemType value);
            
            TItemType& operator[](const TKeyType key);

            void clear();
            size_t count() const;
        
        protected:
            virtual Pair<TKeyType, TItemType> read(ptr_t state) const;
            virtual bool_t next(ptr_t* state) const;
        private:
            TCollectionType list_;

            size_t indexOf(TKeyType key) const;
    };

    #include "sly/collections/map.hpp"

}