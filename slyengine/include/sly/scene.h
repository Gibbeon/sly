#pragma once

#include <thread>

#include "sly/global.h"
#include "sly/engine.h"
#include "sly/gfx.h"
#include "sly/entity.h"
#include "sly/runtime/serializable.h"

namespace sly { 

    struct SimpleMesh : public virtual sly::ISerializable {
    public:
        SLY_TYPEINFO;

        std::vector<gfx::BufferDesc> buffers;
        gfx::RenderStateDesc state;
        
        sly::retval<void> serialize(sly::ISerializer& archive) {
            

            return sly::success();
        }

        sly::retval<void> deserialize(sly::IDeserializer& archive) {
            auto bufferArray = archive.array("buffers");

            for(size_t i = 0; i < bufferArray->size(); i++) {
                gfx::BufferDesc buffer;
                bufferArray->read(i, buffer);
                buffers.push_back(buffer);
            }
            
            archive.read("state", state);

            return sly::success();
        }
    };

    struct EntityDesc : public virtual sly::ISerializable {
    public:
        SLY_TYPEINFO;

        std::string name;
        std::string type;
        
        std::shared_ptr<ISerializable> data;

        sly::retval<void> serialize(sly::ISerializer& archive) {
            //archive.begin(*this, name);
            
            archive.write("name", name);
            archive.write("type", getType().name());           
            
            //archive.end();

            return sly::success();
        }

        sly::retval<void> deserialize(sly::IDeserializer& archive) {
            archive.read("name", name);
            archive.read("type", type);

            data = archive.create(type.c_str(), "data").result();

            return sly::success();
        }
    };

    struct SceneDesc : public virtual sly::ISerializable {
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
            archive.read("name", name);
            archive.read("type", type);

            auto array = archive.array("entities");
            for(size_t i = 0; i < array->size(); i++) {
                EntityDesc desc;            
                array->read(i, desc);
                entities.push_back(desc);
            }

            return sly::success();
        }
    };
        
    class Scene {
    public:
        Scene(const Engine& engine) : 
            _engine(engine) {

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
            //_engine.gfx().draw([&]() {
            //    DrawGraph graph;
                 
            //    for(auto entity : _entities) {
            //        entity->draw(camera, graph);
            //    }
             //   return graph;
           //});                     

            return success();
        }

        retval<void> load(gsl::czstring<> name) {
            auto resources = _engine.resources().find(name).result();
            for(auto resource : resources) {
                auto res = resource.create<SceneDesc>();
                LOG_DEBUG("Loaded Res?");
            }

            return success();
        }

    private:    
        const Engine&               _engine;   
        Camera                      _camera;        
        std::vector<Entity*>        _entities;
    };
}



