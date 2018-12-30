#pragma once

#include "sly/global.h"
#include "sly/builder.h"

namespace sly {
    namespace gfx {
        struct DataBufferDesc {
        public:
        };

        class DataBufferBuilder : public Builder<DataBufferDesc> {
        public:
        };

        class IDataBuffer {
        public:
        };
    }
}