#include "sly/signalconnection.h"
#include "sly/signalreceiver.h"
#include "sly/signal.h"

using namespace sly;

SignalConnection::SignalConnection(Signal& parent, std::function<void(SignalValue, va_list)> command) : 
    _command(command)//, 
    //_parent(&parent)
    {
        
    _terminate = [&](SignalConnection& self){ parent.terminate(*this);  };
}

SignalConnection::SignalConnection(Signal& parent, SignalReceiver& reciever)  {
    reciever.connect(*this);
    _command    = [&](SignalValue value, va_list args){ reciever.accept(value, args); };
    _terminate  = [&](SignalConnection& self){ reciever.terminate(self); parent.terminate(self); };
}

void SignalConnection::transmit(SignalValue value, va_list args) {
    _command(value, args);            
}

void SignalConnection::terminate() {
    _terminate(*this);
           
}

bool_t SignalConnection::operator==(const SignalConnection& other) {
    return this == &other;
}

