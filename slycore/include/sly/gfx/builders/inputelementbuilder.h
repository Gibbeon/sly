#pragma once

#include <string>

#include "sly/global.h"
#include "sly/builder.h"
#include "sly/gfx/enums.h"

namespace sly {
    namespace gfx {
             
        struct InputElementDesc {
        public:
            InputElementDesc() : offset(0) {}

            std::string semanticName;
            eDataFormat format;
            eDataInputClassification scope;
            size_t offset;
        };
        
        class InputElementBuilder : public Builder<InputElementDesc> {
        public:
            InputElementBuilder() : Builder() {}
            virtual ~InputElementBuilder() {}

            InputElementBuilder& setSemanticName(std::string name) { desc_.semanticName = name; return * this;}
            InputElementBuilder& setFormat(eDataFormat format) {desc_.format = format; return * this;}
            InputElementBuilder& setInputScope(eDataInputClassification scope) {desc_.scope = scope; return * this;}
            InputElementBuilder& setOffset(size_t offset) {desc_.offset = offset; return * this;}
        };
    }
}
