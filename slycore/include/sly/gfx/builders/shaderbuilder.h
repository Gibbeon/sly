#pragma once

#include <string>

#include "sly/global.h"
#include "sly/builder.h"
#include "sly/gfx/resource.h"

namespace sly {
    namespace gfx {

        ENUM_DECL(eShaderType,
            eShaderType_Vertex,
            eShaderType_Pixel
        );
    
        struct ShaderDesc  : public virtual sly::ISerializable {
        public:
            SLY_TYPEINFO;

            eShaderType shaderType;
            std::string data;
            size_t size;
            std::string entry;
            std::string target;
            std::string name;

            sly::retval<void> serialize(sly::ISerializer& archive) {
                //archive.begin(*this, name);
                
                archive.write("name", name);
                //archive.write("type", getType().name());
                //archive.write("data", data);
                archive.write("entryPoint", entry);
                archive.write("target", target);

                //archive.end();

                return sly::success();
            }

            sly::retval<void> deserialize(sly::IDeserializer& archive) {
                archive.property("shaderType").read(shaderType);
                archive.property("data").read(data);
                archive.property("entryPoint").read(entry);
                archive.property("target").read(target);
                archive.property("name").read(name);

                size = data.length();

                return sly::success();
            }
        };

        
        
        class ShaderBuilder : public Builder<ShaderDesc> {
        public:
            ShaderBuilder() : Builder() {}
            virtual ~ShaderBuilder() {}

            ShaderBuilder& setData(std::string data, size_t size) { _descriptor.data = data; _descriptor.size = size; return * this; }
            ShaderBuilder& setEntryPoint(gsl::zstring<> entry) { _descriptor.entry = entry; return * this; }
            ShaderBuilder& setTarget(gsl::zstring<> target) { _descriptor.target = target; return * this; }
            ShaderBuilder& setName(gsl::zstring<> name) { _descriptor.name = name; return * this; }
        };
    }
}
