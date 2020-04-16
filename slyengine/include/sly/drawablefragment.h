#pragma once

#include "sly/global.h"
#include "sly/gfx.h"

namespace sly {

    struct DrawableFragmentDesc : ISerializable {
        SLY_TYPEINFO;

        uint_t                                      startInstanceLocation;
        uint_t                                      instanceCount;
        uint_t                                      vertexCount;
        uint_t                                      startLocation;
        int_t                                       baseVertexLocation;

            sly::retval<void> serialize(sly::ISerializer& archive) {
            return sly::success();
        }

        sly::retval<void> deserialize(sly::IDeserializer& archive) {            
            DESERIALIZE(startInstanceLocation);
            DESERIALIZE(instanceCount, 1);
            DESERIALIZE(vertexCount);
            DESERIALIZE(startLocation);
            DESERIALIZE(baseVertexLocation);


            return sly::success();
        }
    };

    class DrawableFragment {
    public:
        retval<void> init(DrawableFragmentDesc desc) {
            _startInstanceLocation = desc.startInstanceLocation;
            _instanceCount = desc.instanceCount;
            _countPerInstance = desc.vertexCount;
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



