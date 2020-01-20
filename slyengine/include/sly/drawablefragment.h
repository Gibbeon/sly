#pragma once

#include "sly/global.h"
#include "sly/gfx.h"

namespace sly {
    class DrawableFragment {
    public:
        retval<void> drawIndexed(gfx::ICommandList& list) const {
            return failed();
        }        
        retval<void> drawNonIndexed(gfx::ICommandList& list) const {
            list.draw(_startInstanceLocation, _instanceCount, _countPerInstance, _startLocation);          
        }
        
    protected:
        uint_t                                      _startInstanceLocation;
        uint_t                                      _instanceCount;
        uint_t                                      _countPerInstance;
        uint_t                                      _startLocation;
        int_t                                       _baseVertexLocation;
    };
}



