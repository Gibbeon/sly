#pragma once

#include "sly/global.h"
#include "sly/function.h"
#include "sly/collections/collection.h"
#include "sly/sys/memory.h"
#include "sly/math/math.h"

namespace sly {

    template <typename TItemType>
    class LinkedList : public Collection<TItemType>
    {
        public:
            LinkedList();
            ~LinkedList();
            
            size_t add(const TItemType item);
            void addRange(const TItemType* array, size_t count);

            void insert(size_t index, const TItemType item);
            void remove(size_t index);
            
            TItemType get(size_t index) const;
            void set(size_t index, const TItemType item);

            void clear();

            TItemType& operator[](const size_t index);

            size_t count() const;
        
        protected:
            virtual TItemType read(ptr_t state) const;
            virtual bool_t next(ptr_t* state) const;

        private:
            typedef struct ListNode {
                TItemType value;
                ListNode* next;
            } ListNode;

            ListNode* head_;
            ListNode* tail_;

            size_t count_;

            ListNode* nodeAt(size_t index) const;
            ListNode* createNode();
            void freeNode(ListNode* node);
    };

    #include "sly/collections/linkedlist.hpp"

}