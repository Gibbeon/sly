#pragma once

#include "sly/global.h"
#include "sly/gfx.h"
#include "sly/spatial.h"
#include "sly/drawable.h"
//#include "sly/drawframe.h"
#include "sly/camera.h"

#include "sly/camera.h"

namespace sly { 
    struct EntityState {
        bool_t visible;
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

    
    struct SimpleMesh : public sly::ISerializable {
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

    class Entity {
    public:
        Entity() {}

        virtual retval<void> init(EntityDesc& desc) {
            sly::ISerializable* serial = &(*desc.data);
            SimpleMesh* desc2 = (SimpleMesh*)(serial);
            
                drawableDesc.buffers = desc2->buffers;
                drawableDesc.state = desc2->state;  

                return success();      
        }

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

            for(auto& entity : _children) {
                entity->update(_global);
            }
            
            return success();
        }

        virtual retval<void> draw(
            gfx::IRenderContext& context, 
            gfx::ICommandList& list, 
            Camera& camera
                        //, DrawFrame& drawgraph
                        //, SoundGraph& soundgroup
                        ) {

            if(!_drawable.has_value()) {
                _drawable.emplace(Drawable(context.getDevice()));
                _drawable->init(drawableDesc);
            }
            
            if(_drawable.has_value()) {
                _drawable->draw(list);
            }

        


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

            return failed<Drawable&>();
        }

    protected:
        Spatial                 _local;
        Spatial                 _global;
        EntityState             _state;

        DrawableDesc drawableDesc;

        std::optional<Entity*>  _parent;
        std::optional<Drawable> _drawable;
        std::vector<Entity*>    _children;
    };
}

    



