#pragma once

#include "sly/global.h"
#include "sly/io/iostream.h"

namespace sly {
    namespace os {

        class File {
        public:
            File(): _stream(nullptr) {

            }

            File(std::shared_ptr<IInputOutputStream> stream): _stream(stream) {

            }

            ~File() {

            }
            
            retval<std::shared_ptr<IInputOutputStream>> stream() const { 
                return _stream; 
            } 

            retval<void> close() { 
                if(_stream) {
                    _stream->close(); 
                    _stream = nullptr;
                }

                return success(); 
            }

        private:
            std::shared_ptr<IInputOutputStream> _stream;
        };     
    }
}