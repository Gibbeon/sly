
#pragma once
#include <vector>

#include "sly/d3d12.h"
#include "sly/d3d12/gfx/device.h"

namespace sly {
namespace gfx {
class D3D12DeviceImpl;

struct D3D12DescriptorTableDesc {
   public:
    size_t capacity;
};

class D3D12riptorTableBuilder : public Builder<D3D12DescriptorTableDesc> {
   public:
    D3D12riptorTableBuilder() : Builder() {}

    D3D12riptorTableBuilder& setCapacity(size_t capacity) {
        _descriptor.capacity = capacity;
        return *this;
    }
};

class D3D12DescriptorTableImpl {
   public:
    D3D12DescriptorTableImpl(D3D12DeviceImpl& device);

    retval<void> init(const D3D12DescriptorTableDesc& desc =
                          D3D12riptorTableBuilder().build());
    retval<void> release();

    void alloc(size_t* indicies, size_t count);
    void free(size_t*, size_t count);

    size_t getAt(size_t index);

    size_t getCapacity() { _capacity; }
    size_t getCount() { _count; }

   protected:
    virtual IDevice& getDevice() { return *_device; }
    ID3D12Device& getID3D12Device() { return _device->getID3D12Device(); }
    D3D12DeviceImpl* _device;

    size_t _nextFree;
    size_t getNextFree();

   private:
    std::vector<bool_t> _used;
    size_t _capacity;
    size_t _count;

    ID3D12DescriptorHeap* _descHeap;
    size_t _descHeapStride;
};

}  // namespace gfx
}  // namespace sly
