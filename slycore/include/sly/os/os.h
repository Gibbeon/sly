#pragma once

#include "sly/global.h"
#include "sly/io/istream.h"
#include "sly/io/ostream.h"
#include "sly/builder.h"
#include "sly/ext/pluginmanager.h"

namespace sly {
        
        typedef void (*pfRegisterPlugins) (sly::IPluginManager& );
    namespace os {

        class IFileSystem {
        public:
            virtual ~IFileSystem() {}
            virtual void open(IInputStream** ppStream, const char_t* file) = 0;
            virtual void create(IOutputStream** ppStream, const char_t* file) = 0;
        protected:
            IFileSystem() {}

        };

        class IOperatingSystem {
        public:
            virtual ~IOperatingSystem() {}            

            virtual void init() = 0;
            virtual size_t getPluginRegistrationFunctions(pfRegisterPlugins* ppfRegisterPlugins, size_t max) = 0;

            virtual IFileSystem& FileSystem() = 0;
        protected:
            IOperatingSystem() {}
        };

        struct WindowDesc 
        {
            uint_t width;
            uint_t height;
            std::string pszTitle;
        };

        class WindowBuilder : sly::Builder<WindowDesc>
        {

        };

        class IWindow
        {
        public:        
            virtual ~IWindow() {} 

            virtual void init(WindowDesc& desc) = 0;
            virtual void onRender() = 0;
            virtual bool_t show() = 0;

            // Accessors.
            virtual uint_t getWidth() const  = 0;
            virtual uint_t getHeight() const   = 0;
            virtual std::string getTitle() const   = 0;

            virtual bool_t processMessages() = 0;
        };

    }
}