#pragma once

#include "sly/global.h"
#include "sly/gfx.h"

namespace sly {

    struct DrawableFragmentDesc {
        uint_t                                      startInstanceLocation;
        uint_t                                      instanceCount;
        uint_t                                      countPerInstance;
        uint_t                                      startLocation;
        int_t                                       baseVertexLocation;
    };

    class DrawableFragment {
    public:
        retval<void> init(DrawableFragmentDesc desc) {
            _startInstanceLocation = desc.startInstanceLocation;
            _instanceCount = desc.instanceCount;
            _countPerInstance = desc.countPerInstance;
            _startLocation = desc.startLocation;
            _baseVertexLocation = desc.baseVertexLocation;
            
                return success();      
        }

        retval<void> drawIndexed(gfx::ICommandList& list) const {
            return failed();
        }        
        retval<void> drawNonIndexed(gfx::ICommandList& list) const {
            list.draw(_countPerInstance, _instanceCount, _startLocation, _startInstanceLocation);  
            
                return success();              
        }
        
    protected:
        uint_t                                      _startInstanceLocation;
        uint_t                                      _instanceCount;
        uint_t                                      _countPerInstance;
        uint_t                                      _startLocation;
        int_t                                       _baseVertexLocation;
    };
}



