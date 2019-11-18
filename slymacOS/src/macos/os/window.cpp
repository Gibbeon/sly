#include "sly/macos/os/window.h"

#include "mtlpp/mtlpp.hpp"
#include "mtlpp/examples/window.hpp"

#import <Cocoa/Cocoa.h>
#import <MetalKit/MetalKit.h>
#include <stdio.h>

class MtlView : public ns::Object
    {
    public:
        MtlView() { }
        MtlView(const ns::Handle& handle) : ns::Object(handle) { }

        mtlpp::Drawable GetDrawable() const
        {
        return ns::Handle{ (__bridge void*)((__bridge MTKView*)this->GetPtr()).currentDrawable };
        }

        mtlpp::RenderPassDescriptor GetRenderPassDescriptor() const
        {
        return ns::Handle{ (__bridge void*)((__bridge MTKView*)this->GetPtr()).currentRenderPassDescriptor };
        }
    };

@interface WindowViewController : NSViewController<MTKViewDelegate> {
    @public void (*m_render)(const sly::os::MacOSWindow&);
    @public const sly::os::MacOSWindow* m_window;
}

@end

@implementation WindowViewController
-(void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size
{

}

-(void)drawInMTKView:(nonnull MTKView *)view
{
    (*m_render)(*m_window);
}
@end

using namespace sly::os;

mtlpp::Device              g_device;
mtlpp::CommandQueue        g_commandQueue;
mtlpp::Buffer              g_vertexBuffer;
mtlpp::RenderPipelineState g_renderPipelineState;
mtlpp::Drawable g_Drawable;
mtlpp::RenderPassDescriptor g_RenderPassDescriptor;


MtlView m_view;

void MacOSWindow::init(WindowDesc& desc) 
{
    m_width = desc.width;
    m_height = desc.height;
    m_title = desc.pszTitle;

    NSRect frame = NSMakeRect(0, 0, m_width, m_height);
    NSWindow* window = [[NSWindow alloc] initWithContentRect:frame
#if MTLPP_IS_AVAILABLE_MAC(10_12)
        styleMask:(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable)
#else
        styleMask:(NSTitledWindowMask | NSClosableWindowMask | NSResizableWindowMask)
#endif
        backing:NSBackingStoreBuffered
        defer:NO];
    window.title = [[NSProcessInfo processInfo] processName];
    WindowViewController* viewController = [WindowViewController new];
    viewController->m_render = onRender;
    viewController->m_window = this;

    g_device = mtlpp::Device::CreateSystemDefaultDevice();
    

    MTKView* view = [[MTKView alloc] initWithFrame:frame];
    view.device = (__bridge id<MTLDevice>)g_device.GetPtr();
    view.delegate = viewController;
    view.autoresizingMask = NSViewWidthSizable | NSViewHeightSizable;

    [window.contentView addSubview:view];
    [window center];
    [window orderFrontRegardless];

    m_view = ns::Handle{ (__bridge void*)view };
}

bool_t MacOSWindow::processMessages()
{
    const char shadersSrc[] = R"""(
        #include <metal_stdlib>
        using namespace metal;
        vertex float4 vertFunc(
            const device packed_float3* vertexArray [[buffer(0)]],
            unsigned int vID[[vertex_id]])
        {
            return float4(vertexArray[vID], 1.0);
        }
        fragment half4 fragFunc()
        {
            return half4(1.0, 0.0, 0.0, 1.0);
        }
    )""";

    const float vertexData[] =
    {
         0.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
    };
    
    g_commandQueue = g_device.NewCommandQueue();

    mtlpp::Library library = g_device.NewLibrary(shadersSrc, mtlpp::CompileOptions(), nullptr);
    mtlpp::Function vertFunc = library.NewFunction("vertFunc");
    mtlpp::Function fragFunc = library.NewFunction("fragFunc");

    g_vertexBuffer = g_device.NewBuffer(vertexData, sizeof(vertexData), mtlpp::ResourceOptions::CpuCacheModeDefaultCache);

    mtlpp::RenderPipelineDescriptor renderPipelineDesc;
    renderPipelineDesc.SetVertexFunction(vertFunc);
    renderPipelineDesc.SetFragmentFunction(fragFunc);
    renderPipelineDesc.GetColorAttachments()[0].SetPixelFormat(mtlpp::PixelFormat::BGRA8Unorm);
    g_renderPipelineState = g_device.NewRenderPipelineState(renderPipelineDesc, nullptr);

    //Window win(g_device, &OnRender, 320, 240);
    NSApplication * application = [NSApplication sharedApplication];
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

    //NSMenu* menubar = [NSMenu new];
    //NSMenuItem* appMenuItem = [NSMenuItem new];
    //NSMenu* appMenu = [NSMenu new];
    //NSMenuItem* quitMenuItem = [[NSMenuItem alloc] initWithTitle:@"Quit" action:@selector(stop:) keyEquivalent:@"q"];
    //[menubar addItem:appMenuItem];
    //[appMenu addItem:quitMenuItem];
    //[appMenuItem setSubmenu:appMenu];
    //[NSApp setMainMenu:menubar];

    [NSApp activateIgnoringOtherApps:YES];
    [NSApp run];

    return true;
}

void MacOSWindow::onRender(const sly::os::MacOSWindow& window)
{
//while(true) {
        mtlpp::CommandBuffer commandBuffer = g_commandQueue.CommandBuffer();
        
        mtlpp::RenderPassDescriptor renderPassDesc = m_view.GetRenderPassDescriptor();
        if (renderPassDesc)
        {
            mtlpp::RenderCommandEncoder renderCommandEncoder = commandBuffer.RenderCommandEncoder(renderPassDesc);
            renderCommandEncoder.SetRenderPipelineState(g_renderPipelineState);
            renderCommandEncoder.SetVertexBuffer(g_vertexBuffer, 0, 0);
            renderCommandEncoder.Draw(mtlpp::PrimitiveType::Triangle, 0, 3);
            renderCommandEncoder.EndEncoding();
            commandBuffer.Present(m_view.GetDrawable());
        }

        commandBuffer.Commit();
        commandBuffer.WaitUntilCompleted();
    //}
}