#pragma once

#include "sly/global.h"
#include "sly/os/builders/windowbuilder.h"

namespace sly {
    namespace os {
        class IWindow
        {
        public:        
            virtual ~IWindow() {} 

            virtual retval<void> init(WindowDesc& desc) = 0;
            virtual void onRender() = 0;
            virtual bool_t show() = 0;

            // Accessors.
            virtual uint_t getWidth() const  = 0;
            virtual uint_t getHeight() const   = 0;
            virtual std::string getTitle() const   = 0;

            virtual bool_t processMessages() = 0;
        
        protected:
            IWindow() {}
        };
    }
}