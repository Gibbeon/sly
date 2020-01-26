#pragma once

#include <thread>
#include <mutex>

#include "sly/global.h"
#include "sly/io/outputstream.h"

namespace sly {

    class LogWriter {
    public:
        LogWriter() : 
            _async(FALSE),
            _thread(std::thread([](LogWriter* self) { LogWriter::run(self); }, this)) {
        }

        void init(IOutputStream* stream) {
            _stream = std::unique_ptr<sly::IOutputStream>(stream);
        }
        void write(std::string message) {            
            static std::mutex mutex;
            std::unique_lock lock(mutex);
            
            _messages.push_back(message);
            if(!_async) {
                flush();
            }
        }
        
        void flush() {            
            static std::mutex mutex;
            if(_messages.size() > 0) {
                std::unique_lock lock(mutex);
                for(auto msg : _messages) {
                    if(msg.length() > 2048) {
                        printf("WTF");
                    }
                    _stream->write((vptr_t)msg.c_str(), msg.length());
                }
                _messages.clear();
            }
        }

        void close() {
            _stream->close();
        }

    protected:
        static void run(LogWriter* self) {
            while(self->_async) {
                self->flush();
                std::this_thread::yield();
            }
        }

        std::thread _thread;        
        std::unique_ptr<IOutputStream>  _stream;
        std::vector<std::string>        _messages; 
        bool_t _async;
    };


}