#pragma once

#include <glm/glm.hpp>

#include "sly/global.h"
#include "sly/gfx.h"
#include "sly/spatial.h"

using namespace glm;

namespace sly {

    ENUM_DECL(eBoundsType,
        eBoundsType_Points,
        eBoundsType_Box,
        eBoundsType_Square,
        eBoundsType_Mesh
    );

    class Bounds {
    public:
        bool_t collision(Bounds&);

        bool_t collision(vec3& pt) {
            // transform
            if(_parent.has_value()) {
                pt *= _parent.value()->matrix();
            }


        }

    protected:
        std::optional<Spatial*>  _parent;
        eBoundsType _type;

        union {
            //IVertexData* _mesh;
            rect_t          _square;
            uint32_t*       _points;
            box_t           _box;
        };
    };
}



