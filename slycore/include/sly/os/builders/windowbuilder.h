#pragma once

#include "sly/global.h"
#include "sly/io/inputstream.h"
#include "sly/io/outputstream.h"
#include "sly/builder.h"

namespace sly {
    namespace os {
        struct WindowDesc 
        {
            uint_t width;
            uint_t height;
            gsl::czstring<> title;
        };

        class WindowBuilder : public sly::Builder<WindowDesc>
        {
        public:
            WindowBuilder() : Builder() {}
            virtual ~WindowBuilder() {}

            WindowBuilder& setTitle(gsl::czstring<> name) { _descriptor.title = name; return * this ;}
            WindowBuilder& setWidth(uint_t width) {_descriptor.width = width; return * this;}
            WindowBuilder& setHeight(uint_t height) {_descriptor.height = height; return * this;}
        };
    }
}