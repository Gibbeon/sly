

#include <fcntl.h>
#include <io.h>
#include <iostream>
#include "sly/global.h"

namespace sly {
    class Win32Console {
    public:

        sly::retval<void> initHandle(DWORD STD_HANDLE) {
            
            HANDLE stdHandle = GetStdHandle(STD_HANDLE);
            FILE* stream = nullptr;
            switch(STD_HANDLE) {
                case STD_INPUT_HANDLE:
                    stream = stdin; break;
                case STD_OUTPUT_HANDLE:
                    stream = stdout; break;
                case STD_ERROR_HANDLE:
                    stream = stderr; break;
            }

            if(stdHandle != INVALID_HANDLE_VALUE)
            {
                int fileDescriptor = _open_osfhandle((intptr_t)stdHandle, _O_TEXT);
                if(fileDescriptor != -1)
                {
                    FILE* file = _fdopen(fileDescriptor, STD_HANDLE == STD_INPUT_HANDLE ? "r" : "w");
                    if(file != NULL)
                    {
                        int dup2Result = _dup2(_fileno(file), _fileno(stream));
                        if (dup2Result == 0)
                        {
                            setvbuf(stream, NULL, _IONBF, 0);                        
                            return sly::success();
                        }
                    }
                }
            }
            return sly::failed();
        }

        sly::retval<void> init() {
            if (AllocConsole()) {
                _sopen_s(&fout, "CONOUT$", _O_WRONLY, _SH_DENYNO, _S_IWRITE);

                SetStdHandle(STD_INPUT_HANDLE, (HANDLE)_get_osfhandle(fout));
                SetStdHandle(STD_OUTPUT_HANDLE, (HANDLE)_get_osfhandle(fout));
                SetStdHandle(STD_ERROR_HANDLE, (HANDLE)_get_osfhandle(fout));

                SetConsoleTitle("Sly Debug Console");

                FILE* dummyFile;
                freopen_s(&dummyFile, "nul", "r", stdin);
                freopen_s(&dummyFile, "nul", "w", stdout);
                freopen_s(&dummyFile, "nul", "w", stderr);
                
                initHandle(STD_INPUT_HANDLE);
                initHandle(STD_OUTPUT_HANDLE);
                initHandle(STD_ERROR_HANDLE);
    
                std::wcin.clear();
                std::cin.clear();
        
                std::wcout.clear();
                std::cout.clear();
        
                std::wcerr.clear();
                std::cerr.clear();

                return sly::success();
            }
            return sly::failed();
        }

        sly::retval<void> release() {
            _close(fout);

            if(FreeConsole()) {
                return sly::success();
            }
            return sly::failed();
        }
    protected:
        int fout;
    };
}