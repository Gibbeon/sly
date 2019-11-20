#include "sly/metal/gfx/commandlist.h"
#include "sly/metal/gfx/device.h"
#include "sly/metal/gfx/convert.h"
#include "sly/metal/dxh.h"

using namespace sly::gfx;

METALCommandListImpl::METALCommandListImpl(METALDeviceImpl& device) : _device(device), _renderState(NULL) 
{

}

void METALCommandListImpl::init(CommandListDesc& desc) {
    //getIMETALDevice().CreateCommandAllocator(METAL_COMMAND_LIST_TYPE_DIRECT, IID_IMETALCommandAllocator, reinterpret_cast<vptr_t*>(&_allocator));
    //getIMETALDevice().CreateCommandList(0, METAL_COMMAND_LIST_TYPE_DIRECT,_allocator, NULL, IID_IMETALCommandList, reinterpret_cast<vptr_t*>(&_list));
    //_list->Close();
}

void METALCommandListImpl::begin() {
    _encoder = _list.RenderCommandEncoder(renderPassDesc);
    //_allocator->Reset();
    //_list->Reset(_allocator, _renderState == nullptr ? nullptr : &_renderState->getIMETALPipelineState()); // need to see if we should have pipeline state be here 
}

void METALCommandListImpl::end() {
    
    // I think this should be done inside the render target itself somehow?
    // Indicate that the back buffer will now be used to present.
    //_list->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(&_target->getIMETALResource(), METAL_RESOURCE_STATE_RENDER_TARGET, METAL_RESOURCE_STATE_PRESENT));
    //_list->Close();
}

void METALCommandListImpl::setRenderTarget(IRenderTarget& target) {
    //_target = reinterpret_cast<METALRenderTargetImpl*>(&target);
            // Indicate that the back buffer will be used as a render target.
    //_list->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(&_target->getIMETALResource(), METAL_RESOURCE_STATE_PRESENT, METAL_RESOURCE_STATE_RENDER_TARGET));
    
    //METAL_CPU_DESCRIPTOR_HANDLE rtvHandle;
    //rtvHandle.ptr = _target->getBufferLocation();

    //_list->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);
}

void METALCommandListImpl::setRenderState(IRenderState& state) {
    //_renderState = reinterpret_cast<METALRenderStateImpl*>(&state);
    //_list->SetPipelineState(&_renderState->getIMETALPipelineState());
    //_list->SetComputeRootSignature(&_renderState->getIMETALRootSignature());
    //_list->SetGraphicsRootSignature(&_renderState->getIMETALRootSignature());
}

void METALCommandListImpl::setViewport(Viewport& viewport) {
    //_list->RSSetViewports(1, &METAL_VIEWPORT_CAST(viewport));
}

void METALCommandListImpl::setScissorRect(sly::rect_t rect) {
    //_list->RSSetScissorRects(1, &METAL_RECT_CAST(rect));
}

void METALCommandListImpl::setVertexBuffer(IVertexBuffer& buffer) {    
    //_list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    //METAL_VERTEX_BUFFER_VIEW view;

    //view.BufferLocation = buffer.getBufferLocation();    
    //view.SizeInBytes = (UINT)buffer.getSizeInBytes();    
    //view.StrideInBytes = (UINT)buffer.getStrideInBytes();

    //_list->IASetVertexBuffers(0, 1, &view);
}
            
void METALCommandListImpl::clear(color_t color) {
    //METAL_CPU_DESCRIPTOR_HANDLE rtvHandle;
    //rtvHandle.ptr = _target->getBufferLocation();

    //const float clearColor[] = { 0.4f, 0.4f, 0.4f, 1.0f };
    //_list->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
}

void METALCommandListImpl::draw(size_t a, size_t b, size_t c, size_t d) {
    //_list->DrawInstanced((UINT)a, (UINT)b, (UINT)c, (UINT)d);
}
