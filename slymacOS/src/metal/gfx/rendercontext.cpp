#include "sly/metal/gfx/rendercontext.h"
#include "sly/metal/gfx/device.h"
#include "sly/metal/gfx/commandqueue.h"
#include "sly/macOS/os/window.h"

using namespace sly::gfx;
METALRenderContextImpl::METALRenderContextImpl(METALDeviceImpl& device, sly::os::MacOSWindow& window) :
    _window(&window),
    _fence(device),
    _directCommandQueue(device),
    _desctriptorTable(device),
    _device(&device) {

}

void METALRenderContextImpl::init(RenderContextDesc& desc) {
    /*METALriptorTableBuilder descTableBuilder;

    descTableBuilder.setCapacity(2);
    
    _desctriptorTable.init(descTableBuilder.build());
    CommandQueueBuilder builder;
    _directCommandQueue.init(builder.build());
   
    // ribe and create the swap chain.
    DXGI_SWAP_CHAIN_DESC1 swapChain = {};
    swapChain.BufferCount = 2; // how many buffers we will have, 2 allows us to have one actively being written to whilest the other is displayed
    swapChain.Width = _window->getWidth();
    swapChain.Height = _window->getHeight();
    swapChain.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // the color format for the buffer
    swapChain.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // how this buffer is to be used
    swapChain.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // discard the buffer after it's displayed
    swapChain.SampleDesc.Count = 1; // for multisampling the image

    reinterpret_cast<METALDeviceImpl*>(&getDevice())->getIDXGIFactory4().CreateSwapChainForHwnd(
        &_directCommandQueue.getIMETALCommandQueue(),        // Swap chain needs the queue so that it can force a flush on it.
        _window->getHwnd(),
        &swapChain,
        nullptr,
        nullptr,
        reinterpret_cast<IDXGISwapChain1**>(&_swapChain)
        );

    // This sample does not support fullscreen transitions.
    //ThrowIfFailed(factory->MakeWindowAssociation(Win32Application::GetHwnd(), DXGI_MWANO_ALT_ENTER));

    _drawFrameIndex = _swapChain->GetCurrentBackBufferIndex();

    size_t indicies[2];
    _desctriptorTable.alloc(indicies, 2);

    // Create a RTV for each frame.
    for (UINT n = 0; n < 2; n++)
    {
        METAL_CPU_DESCRIPTOR_HANDLE rtvHandle;
        rtvHandle.ptr = _desctriptorTable.getAt(indicies[n]);

        IMETALResource* ptr = nullptr;
        _swapChain->GetBuffer(n, IID_IMETALResource, reinterpret_cast<vptr_t*>(&ptr)); // gets the resource

        getIMETALDevice().CreateRenderTargetView(ptr, 0, rtvHandle); // writes the location of a render target view heap entry at the heap location
        
        _renderTargets[n].init(ptr, rtvHandle.ptr);
    }    */
}

void  METALRenderContextImpl::update()
{
    _window->processMessages();
}

void METALRenderContextImpl::setVisible(bool_t show)
{
    //_window->show();
}

void METALRenderContextImpl::present()
{
    _window->onRender();

    // Present the frame.
    /*if(FAILED(_swapChain->Present(1, 0)))
    {
       HRESULT res = getIMETALDevice().GetDeviceRemovedReason();
       ThrowIfFailed(res);
    }

    // Wait for the command list to execute; we are reusing the same command 
    // list in our main loop but for now, we just want to wait for setup to 
    // complete before continuing. Not ideal!

    // Signal and increment the fence value.
    // if the command queue didn't do anything this will hang!!!
    //fence_.waitFor(directCommandQueue.getIMETALCommandQueue());

    _drawFrameIndex = _swapChain->GetCurrentBackBufferIndex();
    */
}

