#pragma once

#include <string>

#include "sly/global.h"
#include "sly/builder.h"
#include "sly/gfx/enums.h"

namespace sly {
    namespace gfx {
             
        struct InputElementDesc: public virtual ISerializable {
        public:
            SLY_TYPEINFO;
            
            std::string semanticName;
            eDataFormat format;
            eDataInputClassification scope;
            uint_t offset;

            sly::retval<void> serialize(sly::ISerializer& archive) {

                return sly::success();
            }

            sly::retval<void> deserialize(sly::IDeserializer& archive) { 
                scope = eDataInputClassification_PerVertex;
                offset = 0;

                std::string type_string;
                archive.property("name").read(semanticName);
                archive.property("format").read(type_string);
                format = sly::Enum<eDataFormat>::parse(type_string.c_str());
                archive.property("offset").read(offset);                
                
                return sly::success();
            }
        };
        
        class InputElementBuilder : public Builder<InputElementDesc> {
        public:
            InputElementBuilder() : Builder() 
            {
                _descriptor.offset = 0;
                _descriptor.scope = sly::gfx::eDataInputClassification_PerVertex;
            }

            virtual ~InputElementBuilder() {}

            InputElementBuilder& setSemanticName(gsl::zstring<> name) { _descriptor.semanticName = name; return * this;}
            InputElementBuilder& setFormat(eDataFormat format) {_descriptor.format = format; return * this;}
            InputElementBuilder& setInputScope(eDataInputClassification scope) {_descriptor.scope = scope; return * this;}
            InputElementBuilder& setOffset(size_t offset) {_descriptor.offset = offset; return * this;}
        };
    }
}

