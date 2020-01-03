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
            std::string pszTitle;
        };

        class WindowBuilder : public sly::Builder<WindowDesc>
        {
        public:
            WindowBuilder() : Builder() {}
            virtual ~WindowBuilder() {}

            WindowBuilder& setTitle(std::string name) { desc_.pszTitle = name; return * this ;}
            WindowBuilder& setWidth(uint_t width) {desc_.width = width; return * this;}
            WindowBuilder& setHeight(uint_t height) {desc_.height = height; return * this;}
        };
    }
}