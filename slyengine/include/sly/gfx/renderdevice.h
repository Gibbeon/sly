#pragma once

#include "sly/global.h"
#include "sly/builder.h"

namespace sly {
    namespace gfx {
    
        struct DeviceDesc {
        public:
        };

        class DeviceBuilder : public Builder<DeviceDesc> {
        };

        class IWindow;
        class ICommandList;
        class IDataBuffer;
        class IShader;
        class ITexture;

        struct WindowDesc;
        struct CommandListDesc;
        struct DataBufferDesc;
        struct ShaderDesc;
        struct TextureDesc;

        class IDevice {
        public:
            void createWindow(out_ptr_t<IWindow> ppWindow, ref_t<WindowDesc> desc);
            void createCommandList(out_ptr_t<ICommandList> ppWindow, ref_t<CommandListDesc> desc);
            void createDataBuffer(out_ptr_t<IDataBuffer> ppWindow, ref_t<DataBufferDesc> desc);
            void createShader(out_ptr_t<IShader> ppWindow, ref_t<ShaderDesc> desc);
            void createTexture(out_ptr_t<ITexture> ppWindow, ref_t<TextureDesc> desc);
        };
    }
}