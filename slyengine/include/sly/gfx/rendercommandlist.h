#pragma once

#include "sly/global.h"
#include "sly/builder.h"

namespace sly {
    namespace gfx {
        struct CommandListDesc {
        public:
        };

        class CommandListBuilder : public Builder<CommandListDesc> {
        public:
        };

        class ICommandList {
        public:
            void begin();
            void end();

            void setViewport();
            void setCamera();
            void setProjection();
            void setScissorRect();
            void setVSShader();
            void setPSShader();
            void setVertexBuffer();
            void setIndexBuffer();
            void setTexture();
            void drawIndexed();
        };
    }
}