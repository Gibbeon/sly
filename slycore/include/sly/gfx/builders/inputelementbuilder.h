#pragma once

#include <string>

#include "sly/global.h"
#include "sly/builder.h"
#include "sly/gfx/enums.h"

namespace sly {
    namespace gfx {
             
        struct InputElementDesc {
        public:
            gsl::zstring<> semanticName;
            eDataFormat format;
            eDataInputClassification scope;
            size_t offset;
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

