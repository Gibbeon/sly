
#pragma once
#include <vector>

#include "sly/metal.h"
#include "sly/metal/gfx/device.h"

namespace sly {
    namespace gfx {
        class METALDeviceImpl;

        struct METALDescriptorTableDesc {
        public:
            size_t capacity;

        };
        
        class METALDescriptorTableImpl {
        public:
            METALDescriptorTableImpl(METALDeviceImpl& device);

            void init(METALDescriptorTableDesc& desc);

            void alloc(size_t* indicies, size_t count);
            void free(size_t*, size_t count);

            size_t getAt(size_t index);

            size_t getCapacity() { return _capacity; }
            size_t getCount() { return _count; }

        protected:
            virtual IDevice& getDevice() { return *_device; } 
            //ID3D12Device& getID3D12Device()   { return _device->getID3D12Device(); }
            METALDeviceImpl* _device;     

            size_t _nextFree;
            size_t getNextFree();
        
        private:
            std::vector<bool_t> _used;
            size_t _capacity;
            size_t _count;

            //ID3D12DescriptorHeap* _descHeap;
            size_t _descHeapStride;  
        };        

        class METALriptorTableBuilder : public Builder<METALDescriptorTableDesc> {
        public:
            METALriptorTableBuilder() : Builder() {}

            METALriptorTableBuilder& setCapacity(size_t capacity) { desc_.capacity = capacity; return *this; }

        };
    }
}

