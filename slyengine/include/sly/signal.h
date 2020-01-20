#pragma once

#include "sly/global.h"
#include "sly/signalvalue.h"
#include "sly/signalconnection.h"

namespace sly {

    class SignalReceiver;
    class SignalConnection;
    class Signal {
    public:
        ~Signal();
        void emit(SignalValue, ...);
        void connect(SignalReceiver&);
        void connect(std::function<void(SignalValue, va_list)>);
        void terminate(SignalConnection&);

    protected:
        std::vector<SignalConnection> _connections;
    };
}


