
#pragma once

#include "sly/d3d12.h"
#include "sly/collections/list.h"
#include "sly/d3d12/gfx/managed.h"

namespace sly {
    namespace gfx {
        class D3D12DeviceImpl;

        struct D3D12DescriptorTableDesc {
        public:
            size_t capacity;

        };
        
        class D3D12DescriptorTableImpl : public D3D12ManagedImpl {
        public:
            D3D12DescriptorTableImpl(ref_t<D3D12DeviceImpl> device);

            void init(ref_t<D3D12DescriptorTableDesc> desc = DEFAULT_DESC);

            void alloc(Array<size_t>& indicies, size_t count);
            void free(Array<size_t>& indicies, size_t count);

            size_t getAt(size_t index);

            size_t getCapacity() { return capacity_; }
            size_t getCount() { return count_; }

        protected:
            using D3D12ManagedImpl::D3D12ManagedImpl;

            size_t nextFree_;
            size_t getNextFree();
        
        private:
            List<bool_t> used_;
            size_t capacity_;
            size_t count_;

            ref_t<ID3D12DescriptorHeap> descHeap_;
            size_t descHeapStride_;

            constexpr static D3D12DescriptorTableDesc DEFAULT_DESC = { 32 /* capacity */ };
            friend class D3D12DescriptorTableBuilder;    
        };        

        class D3D12DescriptorTableBuilder : public Builder<D3D12DescriptorTableDesc> {
        public:
            D3D12DescriptorTableBuilder() : Builder(D3D12DescriptorTableImpl::DEFAULT_DESC) {}

            D3D12DescriptorTableBuilder& setCapacity(size_t capacity) { desc_.capacity = capacity; return *this; }

        };
    }
}

