#pragma once

#include "sly/global.h"
#include "sly/io/iostream.h"

namespace sly {
    namespace os {

        class File {
        public:
            File(): _stream(nullptr) {

            }

            File(IInputOutputStream* stream): _stream(stream) {

            }

            ~File() {
                
            }
            
            //File( File const& )              = delete;
            //File( File && )                  = delete;
            //File& operator = ( File const& ) = delete;
            //File& operator = ( File && )     = delete;

            retval<IInputOutputStream&> stream() const { return *_stream; }    
            retval<void> close() { 
                if(_stream) {
                    _stream->close(); 
                    delete _stream;
                    _stream = nullptr;
                }

                return success(); 
            }

        private:
            gsl::owner<IInputOutputStream*> _stream;
        };     
    }
}