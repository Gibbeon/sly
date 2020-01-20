#pragma once

#include "sly/global.h"
#include "sly/gfx.h"
#include "sly/spatial.h"
#include "sly/drawable.h"
#include "sly/drawgraph.h"
#include "sly/camera.h"

namespace sly { 
    struct EntityState {
        bool_t visible;
    };

    class Entity {
    public:
        Entity() {}

        virtual retval<void> update() {
            if(_local.updated()) {
                if(_parent.has_value()) {
                    update(_parent.value()->global());
                } else {
                    update(Spatial());
                }
                return success();
            }

            for(auto entity : _children) {
                entity->update(_global);
            }
            return success();
        }

        virtual retval<void> update(Spatial& parent) {
            _global = parent.matrix() * _local.matrix();

            for(auto entity : _children) {
                entity->update(_global);
            }
            
            return success();
        }

        virtual retval<void> draw(Camera& camera
                        , DrawGraph& drawgraph
                        //, SoundGraph& soundgroup
                        ) {
            


            return success();
        }

        virtual Spatial& global() {
            return _global; 
        }

        virtual Spatial& local() {
            return _local; 
        }

        virtual bool_t shouldDraw() {
            return _drawable.has_value() && _state.visible;
        }
        
        virtual retval<Drawable&> drawable() {
            if(_drawable.has_value()) {
                return _drawable.value();
            }

            return failed();
        }

    protected:
        Spatial                 _local;
        Spatial                 _global;
        EntityState             _state;

        std::optional<Entity*>  _parent;
        std::optional<Drawable> _drawable;
        std::vector<Entity*>    _children;
    };
}

    



