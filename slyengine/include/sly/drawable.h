#pragma once

#include "sly/global.h"
#include "sly/gfx.h"
#include "sly/drawablefragment.h"

namespace sly {

    class Drawable {
    public:
        retval<void> draw(  gfx::ICommandList& list
                            , uint_t vertexSlot = 0) const {

            list.setVertexBuffer(*_vertexBuffers[0]);

            //IF_EXISTS(_indexBuffer, list.setIndexBuffer(_indexBuffer));

            if(_indexBuffer == nullptr) {
                for(auto& fragment : _fragments) {
                    fragment.drawNonIndexed(list);
                }
            } else {
                for(auto& fragment : _fragments) {
                    fragment.drawIndexed(list);
                }
            }

            return success();   
        }  

        gsl::span<gfx::Material* const> materials() {
            return _materials;
        }
        
        gsl::span<gfx::IVertexBuffer* const> vertexbuffers() {
            return _vertexBuffers;
        }

        std::optional<gfx::IIndexBuffer*>& indexbuffer() {
            return _indexBuffer;
        }

        gsl::span<DrawableFragment> fragments() {
            return _fragments;
        }

    protected:

        std::vector<gfx::Material*>         _materials;
        std::vector<gfx::IVertexBuffer*>    _vertexBuffers;  
        std::optional<gfx::IIndexBuffer*>   _indexBuffer;  
        std::vector<DrawableFragment>       _fragments;
    };
}



