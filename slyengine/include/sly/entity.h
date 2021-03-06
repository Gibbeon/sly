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

    struct EntityDesc {
    public:
        SLY_TYPEINFO;

        std::string name;
        
        DrawableDesc drawable;
        
    };

    class Entity : public sly::ISerializable {
    public:
        SLY_TYPEINFO;
        
        Entity() {}

        retval<void> init(EntityDesc& desc) {
            _name = desc.name;
            drawableDesc = desc.drawable;  
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

        sly::retval<void> serialize(sly::ISerializer& archive) {
            //archive.begin(*this, name);
            
            archive.write("name", _name);  

            return sly::success();
        }

        sly::retval<void> deserialize(sly::IDeserializer& archive) {
            EntityDesc desc;

            archive.property("name").read(desc.name);
            archive.property("drawable").read(desc.drawable);

            return init(desc);
        }

    protected:
        Spatial                 _local;
        Spatial                 _global;
        EntityState             _state;

        DrawableDesc drawableDesc;

        std::optional<Entity*>  _parent;
        std::optional<Drawable> _drawable;
        std::vector<Entity*>    _children;

        std::string             _name;
    };
}

    



