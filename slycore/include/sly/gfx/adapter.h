#include "sly/global.h"
#include "sly/gfx.h"

namespace sly {
    namespace gfx {

        class IRenderAdapter {
            typedef u32 Ident;

            virtual gsl::cstring_span<> description() const = 0;

            virtual u32     index() const = 0;

            virtual Ident   vendorId() const = 0;
            virtual Ident   deviceId() const = 0;
            virtual Ident   subSystemId() const = 0;
            virtual u32     revision() const = 0;
    
            virtual size_t  dedicatedVideoMemory() const = 0;
            virtual size_t  dedicatedSystemMemory() const = 0;
            virtual size_t  sharedSystemMemory() const = 0;
        };
    }
}