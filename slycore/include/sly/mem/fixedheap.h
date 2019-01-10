/* #pragma once

#include "sly/global.h"

namespace sly {
    namespace mem {

        template<size_t BlockSize = 4096>
        class FixedAllocator : public IHeapAllocator {
        public:            
            virtual vptr_t alloc(IHeap& heap, size_t size) {
                size_t blocks_to_scan = (heap.getSize() >> static_log2<BlockSize>) + (heap.getSize() > (1 << static_log2<BlockSize>)) ? 1 : 0;
                size_t blocks_required = (size >> static_log2<BlockSize>) + (size > (1 << static_log2<BlockSize>)) ? 1 : 0;
                size_t blocks_found = 0;

                PointerHeader* table, current = reinterpret_cast<PointerHeader*>(heap.head());
                
                while(blocks_found < blocks_required) {
                    if((current + blocks_found).size == 0) {
                        blocks_found++;
                    }
                    else {
                        blocks_to_scan -= blocks_found + + (current + blocks_found).size;
                        
                        if(blocks_required > blocks_to_scan) {
                            return NULL;
                        }
                        
                        current =+ blocks_found + (current + blocks_found).size;
                        blocks_found = 0;
                    }
                }

                memset(&table[index], blocks_found, table[index].size);
                return heap.head() + (current << (static_log2<BlockSize> + static_log2<sizeof(PointerHeader)>));              
            }

            virtual void free(IHeap& heap, vptr_t ptr) {
                size_t index = (ptr - heap.head()) >> static_log2<BlockSize>
                PointerHeader* table = reinterpret_cast<PointerHeader*>(heap.head());
                memset(&table[index], 0, table[index].size);
            }

        protected:
            struct PointerHeader : u16 {
                union {
                    struct {
                        size_t size;
                    };
                }
                u16 _data;
            };
        };


        template<size_t Size = 1024 * 1024, typename TAllocator = FixedAllocator<>>
        class FixedHeap : public IHeap {
        public:
            virtual vptr_t head() { return reinterpret_cast<vptr_t>(_heap.data()); }
            virtual vptr_t tail() { return reinterpret_cast<vptr_t>(_heap.data() + _size); }
               
            virtual vptr_t alloc(size_t size) { return TAllocator().alloc(*this, size); }
            virtual void free(vptr_t ptr) { return TAllocator().free(*this); }

            virtual size_t getSize() { return _size; }
        protected:
            std::array<u8, Size> _heap;
            size_t _size;
        };
    }
}
 */