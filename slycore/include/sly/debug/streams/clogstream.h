#pragma once

#include <iostream>

#include "sly/global.h"
#include "sly/io/outputstream.h"

namespace sly {
    class CLogStream : public IOutputStream {
    public:
        virtual retval<void> write(vptr_t buffer, size_t size) {
            std::cout.write((const char*)buffer, size);
            return success();
        }

        virtual size_t size() const {
            return 0;            
        }

        virtual size_t position() const{
            return 0;
        }

        virtual retval<void> seek(s64 offset){
            return failed();            
        }

        virtual retval<void> setPosition(size_t position) {
            return failed();
        }

        virtual retval<void> flush(){
            std::clog.flush();     
            return success();       
        }

        virtual retval<void> close(){            
            return success();
        }
    };
}