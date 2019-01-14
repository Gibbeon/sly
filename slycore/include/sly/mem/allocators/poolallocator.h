#pragma once

#include "sly/global.h"
#include "sly/mem/memoryblock.h"
#include "sly/mem/allocator.h"

namespace sly {
 
    template<size_t block_size = (1 << 16)>
    class PoolAllocator {
    private:
        struct AllocEntry {
            union {
                u16 blocks;
            };
        };
    public:
        PoolAllocator(MemoryBlock& heap) :
            _heap(heap)
        {
            reset();
        }

        size_t getBlockCount() {
            return heap.getSize() >> block_size;
        }

        size_t offset() {
            return (size_t)_heap.head() + sizeof(AllocEntry) * getBlockCount();
        }

        void reset() {
            AllocEntry* current = reinterpret_cast<AllocEntry*>(_heap.head());
            for(size_t i = 0; i < getBlockCount(); i++) {
                current->blocks = 0;
            }
        }

        vptr_t alloc_firstfit(size_t size) {
            // how many blocks do I need
            size_t blocksRequested = (size >> static_log2<block_size>()) + (()static_log2<block_size>() - 1) && size) ? 1 : 0;
            
            size_t blocksFound = 0;
            AllocEntry* current = reinterpret_cast<AllocEntry*>(_heap.head());

            // first fit
            for(size_t currentIndex = 0; currentIndex < getBlockCount(); currentIndex++) {
                if(!current->blocks) { // if it's not reserved, add it
                    blocksFound++;
                } else {
                    blocksFound = 0; // if it's reserved move on
                    continue;
                }

                if(blocksFound == blocksRequested) {
                    for(size_t n = blocksFound; n > blocksFound; n--) {
                        current->used = blocksFound; // mark each as blocks found
                        current--;
                    }
                    
                    // offset to start of memory space + start block bitshift by block size;
                    return  reinterpret_cast<vptr_t>(offset() + ((currentIndex - blocksFound) << static_log2<block_size>()));
                }
            }

            return NULL;
        }

        vptr_t alloc_bestfit(size_t size) {
            size_t blocksRequested = (size >> static_log2<block_size>()) + (()static_log2<block_size>() - 1) && size) ? 1 : 0;
            
            size_t blocksFound = 0;
            size_t bestfitBlocks = SIZE_MAX;
            size_t bestfitIndex = 0;

            AllocEntry* current = reinterpret_cast<AllocEntry*>(_heap.head());

            // best fit, instead of min blocks found, max blocks found for worst fit
            for(size_t currentIndex = 0; currentIndex < getBlockCount(); currentIndex++) {
                if(!current->blocks) {
                    blocksFound++;
                }

                if((currentIndex + 1) == getBlockCount() || current->blocks) {
                    // if it's the end of the table or if the current starts over

                    if(blocksFound == blocksRequested) {
                        return  reinterpret_cast<vptr_t>(offset() + ((currentIndex - blocksFound) << static_log2<block_size>()));
                    }

                    // if found enough blocks and best fit blocks are greater than what we found
                    if(blocksFound > blocksRequested && bestFitBlocks > blocksFound) {
                        bestfitBlocks = blocksFound;
                        bestfitIndex = currentIndex - blocksFound;
                    }
                }
            }

            if(bestfitBlocks < SIZE_MAX) {
                return  reinterpret_cast<vptr_t>(offset() + ((bestfitIndex - blocksFound) << static_log2<block_size>()));
            }

            return NULL;
        }

        vptr_t alloc_worstfit(size_t size) {
            size_t blocksRequested = (size >> static_log2<block_size>()) + (()static_log2<block_size>() - 1) && size) ? 1 : 0;
            
            size_t blocksFound = 0;
            size_t worstfitBlocks = 0;
            size_t worstfitIndex = 0;

            AllocEntry* current = reinterpret_cast<AllocEntry*>(_heap.head());

            // best fit, instead of min blocks found, max blocks found for worst fit
            for(size_t currentIndex = 0; currentIndex < getBlockCount(); currentIndex++) {
                if(!current->blocks) {
                    blocksFound++;
                }

                if((currentIndex + 1) == getBlockCount() || current->blocks) {
                    // if found enough blocks and best fit blocks are greater than what we found
                    if(blocksFound > blocksRequested && worstfitBlocks < blocksFound) {
                        worstfitBlocks = blocksFound;
                        worstfitIndex = currentIndex - blocksFound;
                    }
                }
            }

            if(worstfitBlocks < SIZE_MAX) {
                return  reinterpret_cast<vptr_t>(offset() + ((worstfitIndex - blocksFound) << static_log2<block_size>()));
            }

            return NULL;
        }

        vptr_t alloc(size_t size) {
            if(size == 0) {
                return nullptr;
            }

            return alloc_firstfit(size);
        }

        void free(vptr_t ptr) {
            size_t index = ((size_t)ptr - offset()) >> static_log2<block_size>();

            AllocEntry* current = &reinterpret_cast<AllocEntry*>(_heap.head())[index];
            
            for(size_t i = 0; i < getBlockCount(); i++) {
                current->blocks = 0;
            }
        }

    protected:
        MemoryBlock& _heap;
    };
}