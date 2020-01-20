#pragma once

#include "sly/global.h"
#include "sly/gfx.h"
#include "sly/entity.h"
#include "sly/drawable.h"

namespace sly { 

    class DrawGraph {
        retval<void> reset();
        retval<void> commit() {
            _drawables.reserve(_entities.size());
            
            for(auto entity: _entities) {
                _drawables.push_back(entity->drawable());
            }
        }

        retval<void> sort(std::function<int32_t(Entity& rhs, Entity& lhs)>) {
            // non-alpha vs alpha
            // sort by distance from camera
            // sort by textures
            // sort by shaders
            // sort by state
        }

        std::vector<Entity*>&   entities() const;
        std::vector<Drawable>&  drawables() const;

    private:
        std::vector<Entity*>    _entities;
        std::vector<Drawable>   _drawables;
    };
}



