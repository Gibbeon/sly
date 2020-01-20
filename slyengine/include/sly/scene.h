#pragma once

#include <thread>

#include "sly/global.h"
#include "sly/engine.h"
#include "sly/gfx.h"
#include "sly/entity.h"

namespace sly { 
    class Scene {
    public:
        Scene(const Engine& engine) : 
            _engine(engine) {

        }

        retval<void> update() {
            for(auto entity : _entities) {
                entity->update();
            }

            return success();
        }

        retval<void> draw(gfx::IRenderContext& context) {
            for(auto entity : _entities) {
                entity->draw(context);
            }

            return success();
        }

    private:    
        const Engine&               _engine;        
        std::vector<Entity*>        _entities;
    };
}



