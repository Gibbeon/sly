#pragma once

#include "sly/global.h"
#include "sly/io/istream.h"
#include "sly/io/ostream.h"
#include "sly/ext/pluginmanager.h"

namespace sly {
    
    class IFileSystem {
    public:
        virtual ~IFileSystem() {}
        virtual void open(IInputStream** ppStream, const char_t* file) = 0;
        virtual void create(IOutputStream** ppStream, const char_t* file) = 0;
    protected:
        IFileSystem() {}

    };
    
    typedef void (*pfRegisterPlugins) (sly::IPluginManager& );

    class IOperatingSystem {
    public:
        virtual ~IOperatingSystem() {}
        

        virtual void init() = 0;
        virtual size_t getPluginRegistrationFunctions(pfRegisterPlugins* ppfRegisterPlugins, size_t max) = 0;

        virtual IFileSystem& FileSystem() = 0;
    protected:
        IOperatingSystem() {}
    };
    
}