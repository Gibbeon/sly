#pragma once

#include "sly/global.h"
#include "sly/signal.h"

namespace sly {

    class Signal;
    class SignalReceiver;
    class SignalConnection {
    public:
        SignalConnection() {}
        ~SignalConnection() { }
        SignalConnection(Signal& parent, std::function<void(SignalValue, va_list)> command);
        SignalConnection(Signal& parent, SignalReceiver& reciever);

        bool_t operator==(const SignalConnection& other);

        void transmit(SignalValue, va_list args);
        void terminate();
    protected:
    
        //Signal*                                     _parent; 
        std::function<void(SignalConnection&)>      _terminate;  
        std::function<void(SignalValue, va_list)>   _command;   
    };
}


