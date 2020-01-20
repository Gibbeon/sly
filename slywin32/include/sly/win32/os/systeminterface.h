#pragma once

#include <windows.h>
#include <stdio.h>
#include <conio.h>

#include <fstream>

#include "sly/win32.h"
#include "sly/os/operatingsystem.h"
#include "sly/win32/os/filesystem.h"
#include "sly/win32/os/windowsystem.h"
#include "sly/win32/os/console.h"

namespace sly { 
    class Kernel;
    namespace os {
        class Win32SystemInterface : public ISystemInterface {
        public:
            Win32SystemInterface(Kernel&);
            virtual ~Win32SystemInterface();

            virtual retval<void> init();
            virtual retval<void> release();
            
            virtual retval<SystemHandle> loadLibrary(gsl::czstring_span<>);
            virtual retval<SystemHandle> getProcAddress(gsl::czstring_span<>, SystemHandle handle = nullptr);

            virtual IFileSystem& filesystem() const;
            virtual IWindowSystem& windows() const;
            virtual Win32Console& console();

        protected:

        private:
            Kernel&             _kernel;
            Win32FileSystem*    _filesystem;
            Win32WindowSystem*  _windows;
            Win32Console        _console;
        };
    }
}
