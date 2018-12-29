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
            
            s32 add(const TItemType item);
            void addRange(const TItemType* array, s32 count);

            void insert(s32 index, const TItemType item);
            void remove(s32 index);
            
            TItemType get(s32 index) const;
            void set(s32 index, const TItemType item);

            void clear();

            TItemType& operator[](const s32 index);

            s32 count() const;
        
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

            s32 count_;

            ListNode* nodeAt(s32 index) const;
            ListNode* createNode();
            void freeNode(ListNode* node);
    };

    #include "sly/collections/linkedlist.hpp"

}