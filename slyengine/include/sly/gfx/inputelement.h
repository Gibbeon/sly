#pragma once

#include "sly/global.h"
#include "sly/builder.h"
#include "sly/gfx/enums.h"

namespace sly {
    namespace gfx {
             
        struct InputElementDesc {
        public:
            string_t semanticName;
            eDataFormat format;
            eDataInputClassification scope;
            size_t offset;
        };
        
        class InputElementBuilder : public Builder<InputElementDesc> {
        public:
            InputElementBuilder() : Builder(DEFAULT_DESC) {}

            InputElementBuilder& setSemanticName(string_t name) { desc_.semanticName = name; return * this;}
            InputElementBuilder& setFormat(eDataFormat format) {desc_.format = format; return * this;}
            InputElementBuilder& setInputScope(eDataInputClassification scope) {desc_.scope = scope; return * this;}
            InputElementBuilder& setOffset(size_t offset) {desc_.offset = offset; return * this;}

        protected:
            constexpr static InputElementDesc DEFAULT_DESC = { "UNKNOWN", eDataFormat_Default, eDataInputClassification_Default, 0 };
        };
    }
}

