#pragma once

#include <thread>

#include "sly/global.h"
#include "sly/engine.h"
#include "sly/gfx.h"
#include "sly/entity.h"
#include "sly/runtime/serializable.h"

namespace sly { 

    struct SceneDesc : sly::ISerializable {
    public:
        SLY_TYPEINFO;

        Camera                      camera;
        gfx::Viewport               viewport;  
        std::vector<Entity*>        entities;
        gfx::color_t                clearColor;
        sly::rect_t<>               scissorRect;

        virtual sly::retval<void> serialize(sly::ISerializer& archive) {            
            archive.write("type", getType().name());      //begin record      
            //archive.write("name", name);

            return sly::success();
        }

        virtual sly::retval<void> deserialize(sly::IDeserializer& archive) {                        
            DESERIALIZE(clearColor);
            DESERIALIZE(viewport);
            DESERIALIZE(scissorRect);

            {
                auto& __array = archive.open("entities");
                for(size_t i = 0; i < __array.size(); i++) {                          
                    auto result = __array[i].create();
                    if(result.succeeded()) {
                        entities.push_back(&(result.as<Entity&>()));
                    } else {
                        return sly::failed();
                    }
                }
                __array.close();
            }  

            return sly::success();
        }
    };
        
    class Scene : public sly::ISerializable {
    public:
        SLY_TYPEINFO;

        Scene() : _list(nullptr) {}

        virtual retval<void> init(SceneDesc desc) {
            _viewport = desc.viewport;
            _camera = desc.camera;
            _entities = std::move(desc.entities);
            _clearColor = desc.clearColor;
            _scissorRect = desc.scissorRect;

            return success();
        };

        virtual retval<void> update() {            
            for(auto& entity : _entities) {
                entity->update();
            };

            return success();
        }

        virtual retval<void> draw(gfx::IRenderContext& context) {
            draw(context, _camera);

            return success();
        }

        virtual retval<void> draw(gfx::IRenderContext& context, Camera& camera) {

            if(!_list) {
                _list = context.getDevice().createCommandList();
            }

            _list->begin();
            _list->setRenderTarget(context.currentRenderTarget());
            _list->clear(_clearColor);
            _list->setViewport(_viewport);    
            _list->setScissorRect(_scissorRect);

            //_engine.gfx().draw([&]() {
            //    DrawGraph graph;
                 
                for(auto entity : _entities) {
                    entity->draw(context, *_list, camera);//, graph);
                }
             //   return graph;
           //});    

            _list->end();

            std::vector<sly::gfx::ICommandList*> lists;
            lists.push_back(_list);

           context.commandQueue().executeCommandLists(lists);  
           context.commandQueue().flush(); 
      

           return success();
        }

        virtual sly::retval<void> serialize(sly::ISerializer& archive) { 
            return sly::success();
        }

        virtual sly::retval<void> deserialize(sly::IDeserializer& archive) {  
            SceneDesc desc;
            archive.read(desc);      
            return init(desc);
        }

        

    private:      
        Camera                      _camera;
        gfx::Viewport               _viewport;  
        gfx::color_t                _clearColor;
        sly::rect_t<>               _scissorRect;
              
        std::vector<Entity*>        _entities;
        gfx::ICommandList*          _list;
    };
}



