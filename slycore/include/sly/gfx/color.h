#pragma once

#include "sly/global.h"

namespace sly {
    namespace gfx {
        template<typename TColorType = float>
        struct colort_t : public sly::ISerializable {
        public:
            SLY_TYPEINFO;

            virtual sly::retval<void> serialize(sly::ISerializer& archive) {
                return success(); 
            }

            virtual sly::retval<void> deserialize(sly::IDeserializer& archive) { 
                DESERIALIZE(r);
                DESERIALIZE(g);
                DESERIALIZE(b);
                DESERIALIZE(a);
                return success();            
            }

            colort_t() {}
            colort_t(TColorType r, TColorType g, TColorType b, TColorType a) :
                r(r), g(g), b(b), a(a)
            {

            }
            union {
                struct {
                    TColorType r;
                    TColorType g;
                    TColorType b;
                    TColorType a;
                };                
                TColorType data[4];
            };

            operator const TColorType*() { return data; }
        };

        typedef colort_t<float> color_t;
    }
}

