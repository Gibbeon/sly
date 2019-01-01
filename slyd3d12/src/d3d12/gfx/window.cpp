#include "sly/d3d12/gfx/window.h"
#include "sly/d3d12/gfx/device.h"
#include "sly/d3d12/gfx/commandqueue.h"
#include "sly/win32/sys/window.h"
#include "sly/collections/fixedarray.h"

using namespace sly::gfx;
D3D12WindowImpl::D3D12WindowImpl(ref_t<D3D12DeviceImpl> device, ref_t<sly::sys::Win32Window> window) :
    window_(window),
    fence_(device),
    directCommandQueue_(device),
    desctriptorTable_(device),
    D3D12ManagedImpl(device) {
}

void D3D12WindowImpl::init(ref_t<WindowDesc> desc) {
    D3D12DescriptorTableBuilder descTableBuilder;

    descTableBuilder.setCapacity(2);
    
    desctriptorTable_.init(descTableBuilder.build());

    //CommandQueueDesc desc;
    //device->createCommandQueue(commandQueue_, desc); // a command queue allows the queued executeion of command lists
   
    // Describe and create the swap chain.
    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
    swapChainDesc.BufferCount = 2; // how many buffers we will have, 2 allows us to have one actively being written to whilest the other is displayed
    swapChainDesc.Width = window_->GetWidth();
    swapChainDesc.Height = window_->GetHeight();
    swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // the color format for the buffer
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // how this buffer is to be used
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // discard the buffer after it's displayed
    swapChainDesc.SampleDesc.Count = 1; // for multisampling the image

    ThrowIfFailed(getDevice()->getIDXGIFactory4()->CreateSwapChainForHwnd(
        directCommandQueue_.getID3D12CommandQueue().ptr(),        // Swap chain needs the queue so that it can force a flush on it.
        window_->GetHwnd(),
        &swapChainDesc,
        nullptr,
        nullptr,
        reinterpret_cast<IDXGISwapChain1**>(&swapChain_)
        ));

    // This sample does not support fullscreen transitions.
    //ThrowIfFailed(factory->MakeWindowAssociation(Win32Application::GetHwnd(), DXGI_MWA_NO_ALT_ENTER));

    drawFrameIndex_ = swapChain_->GetCurrentBackBufferIndex();

    FixedArray<size_t, 2> indicies;
    desctriptorTable_.alloc(indicies, 2);

    // Create a RTV for each frame.
    for (UINT n = 0; n < 2; n++)
    {
        D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;
        rtvHandle.ptr = desctriptorTable_.getAt(indicies[n]);

        ID3D12Resource* ptr = nullptr;
        swapChain_->GetBuffer(n, IID_ID3D12Resource, reinterpret_cast<void**>(&ptr)); // gets the resource

        getID3D12Device()->CreateRenderTargetView(ptr, 0, rtvHandle); // writes the location of a render target view heap entry at the heap location
        
        renderTargets_[n].init(ptr, rtvHandle.ptr);
    }    
}

void  D3D12WindowImpl::processMessages()
{
    window_->ProcessMessages();
}

void D3D12WindowImpl::setVisible(bool_t show)
{
    window_->Show();
}

void D3D12WindowImpl::swapBuffers()
{
    // Present the frame.
    if(FAILED(swapChain_->Present(1, 0)))
    {
       HRESULT res = getDevice()->getID3D12Device()->GetDeviceRemovedReason();
       ThrowIfFailed(res);
    }

    // Wait for the command list to execute; we are reusing the same command 
    // list in our main loop but for now, we just want to wait for setup to 
    // complete before continuing. Not ideal!

    // Signal and increment the fence value.
    // if the command queue didn't do anything this will hang!!!
    //fence_.waitFor(directCommandQueue_.getID3D12CommandQueue());

    drawFrameIndex_ = swapChain_->GetCurrentBackBufferIndex();
}

