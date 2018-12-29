#pragma once

#include "sly/global.h"
#include "sly/builder.h"

namespace sly {
    struct RenderCommandListDesc {
    public:
    };

    class RenderCommandListDescBuilder : public Builder<RenderCommandListDesc> {
    public:
    };

    class IRenderCommandList {
    public:
        void Begin();
        void End();

        void SetViewport();
        void SetCamera();
        void SetProjection();
        void SetScissorRect();
        void SetVSShader();
        void SetPSShader();
        void SetVertexBuffer();
        void SetIndexBuffer();
        void SetTexture();
        void DrawIndexed();
    };
}