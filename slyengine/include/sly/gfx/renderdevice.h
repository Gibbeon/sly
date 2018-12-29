#pragma once

#include "sly/global.h"
#include "sly/builder.h"

namespace sly {
    
    struct RenderDeviceDesc {
    public:
    };

    class RenderDeviceDescBuilder : public Builder<RenderDeviceDesc> {
    };

    class IRenderWindow;
    class IRenderCommandList;
    class IRenderBuffer;
    class IRenderShader;
    class IRenderTexture;

    struct RenderWindowDesc;
    struct RenderCommandListDesc;
    struct RenderBufferDesc;
    struct RenderShaderDesc;
    struct RenderTextureDesc;

    class IRenderDevice {
    public:
        void CreateRenderWindow(out_ptr_t<IRenderWindow> ppWindow, ref_t<RenderWindowDesc> desc);
        void CreateRenderCommandList(out_ptr_t<IRenderCommandList> ppWindow, ref_t<RenderCommandListDesc> desc);
        void CreateRenderBuffer(out_ptr_t<IRenderBuffer> ppWindow, ref_t<RenderBufferDesc> desc);
        void CreateRenderShader(out_ptr_t<IRenderShader> ppWindow, ref_t<RenderShaderDesc> desc);
        void CreateRenderTexture(out_ptr_t<IRenderTexture> ppWindow, ref_t<RenderTextureDesc> desc);
    };
}