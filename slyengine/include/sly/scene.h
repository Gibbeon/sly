#pragma once

#include <thread>

#include "sly/global.h"
#include "sly/engine.h"
#include "sly/gfx.h"
#include "sly/entity.h"
#include "sly/runtime/serializable.h"

namespace sly { 

    struct SceneDesc : public sly::ISerializable {
    public:
        SLY_TYPEINFO;

        std::string name;
        std::string type;
        std::vector<EntityDesc> entities;

        sly::retval<void> serialize(sly::ISerializer& archive) {
            //archive.begin(*this, name);
            
            archive.write("name", name);
            archive.write("type", getType().name());

            return sly::success();
        }

        sly::retval<void> deserialize(sly::IDeserializer& archive) {
            archive.property("name").read(name);
            archive.property("type").read(type);

            auto& record = archive.open("entities");
            for(size_t i = 0; i < record.size(); i++) {
                EntityDesc desc;            
                record.at(i).read(desc);
                entities.push_back(desc);
            }
            record.close();

            return sly::success();
        }
    };
        
    class Scene {
    public:
        Scene(const Engine& engine) : 
            _engine(engine),
            _list(nullptr) {

        }

        retval<void> update() {            
            for(auto& entity : _entities) {
                entity->update();
            };

            return success();
        }

        retval<void> draw(gfx::IRenderContext& context) {
            draw(context, _camera);

            return success();
        }

        retval<void> draw(gfx::IRenderContext& context, Camera& camera) {

            if(!_list) {
                _list = context.getDevice().createCommandList();
            }

            sly::gfx::Viewport viewport(0, 0, 1024, 768);
            sly::rect_t<> scissorRect(0, 0, 1024, 768);
            sly::gfx::color_t clearColor(.4f, .4f, .4f, 0.5f);

            auto& wtf = context.currentRenderTarget();

            _list->begin();
            _list->setRenderTarget(wtf);
            _list->clear(clearColor);
            _list->setViewport(viewport);    
            _list->setScissorRect(scissorRect);

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

        retval<void> load(gsl::czstring<> name) {
            auto resource = _engine.resources().find(name).result();
            
            auto res = resource.create<SceneDesc>();

            for(auto desc : res->entities) {
                Entity* entity = new Entity();
                entity->init(desc);
                _entities.push_back(entity);
            }

            return success();
        }

    private:    
        const Engine&               _engine;   
        Camera                      _camera;        
        std::vector<Entity*>        _entities;
        gfx::ICommandList*          _list;
    };
}



