#pragma once

#include "sly/global.h"
#include "sly/signal.h"


namespace sly {
    class Signal;
    class SignalConnection;
    class SignalReceiver {
    public:
        SignalReceiver(vptr_t parent) : 
            _parent(parent)
        {
            Ensures(_parent); 

        }

        SignalReceiver( SignalReceiver const& )              = delete;
        SignalReceiver( SignalReceiver && )                  = delete;
        SignalReceiver& operator = ( SignalReceiver const& ) = delete;
        SignalReceiver& operator = ( SignalReceiver && )     = delete;



        void init(std::function<void(SignalReceiver&, SignalValue, va_list)> handler) 
        {
            _handler = handler;
            Ensures(_handler);             
        }

        void accept(SignalValue value, va_list args);
        void connect(SignalConnection& connection);
        void terminate(SignalConnection& connection);

        template<typename T>
        T& parent() const { 
            Expects(_parent); 
            return *reinterpret_cast<T*>(_parent);
        }

    protected:
        vptr_t _parent;
        std::function<void(SignalReceiver&, SignalValue, va_list)>          _handler;
        std::vector<SignalConnection*>                                      _connections;
    };
}


