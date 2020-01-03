#pragma once

#include <windows.h>
#include <stdio.h>
#include <conio.h>

#include <fstream>

#include "sly/win32.h"
#include "sly/io/iostream.h"
#include "sly/win32/os/filesystem.h"

namespace sly { 
namespace os {

    class Win32OperatingSystem : public IOperatingSystem {
    public:
        

        Win32OperatingSystem();
        virtual ~Win32OperatingSystem() {}

        
        virtual retval<void> init(OperatingSystemDesc&) { return success(); }
        
        virtual retval<vptr_t> loadLibrary(std::string);
        virtual retval<vptr_t> getProcAddress(std::string, vptr_t handle = nullptr);

        //virtual size_t getPluginRegistrationFunctions(pfRegisterPlugins* ppfRegisterPlugins, size_t max);

        virtual retval<IFileSystem&> filesystem() { return _fs; }

    protected:

    private:
        Win32FileSystem _fs;
    };
}}