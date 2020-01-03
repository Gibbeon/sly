#pragma once

#include "sly/global.h"
#include "sly/io/iostream.h"

namespace sly {
    namespace os {

        class File {
        public:
            File(IInputOutputStream* stream): _stream(stream) {

            }

            ~File() {
                delete _stream;
            }
            
            File( File const& )              = delete;
            File( File && )                  = delete;
            File& operator = ( File const& ) = delete;
            File& operator = ( File && )     = delete;

            retval<IInputOutputStream&> stream() const { return *_stream; }    

        private:
            gsl::owner<IInputOutputStream*> _stream;
        };     
    }
}