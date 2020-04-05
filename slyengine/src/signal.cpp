#pragma once

#include <stdarg.h>
#include "sly/signal.h"
#include "sly/signalconnection.h"

using namespace sly;


Signal::~Signal() {
    for(auto& connection : _connections) {
        terminate(connection);
    }
}

void Signal::emit(SignalValue value, ...) {       
    for(auto& connection : _connections) {
        va_list args;        
        va_start(args, value);  
        connection.transmit(value, args);
        va_end(args);
    }
}

void Signal::connect(SignalReceiver& reciever) {
    _connections.push_back(SignalConnection(*this, reciever));       
}

void Signal::connect(std::function<void(SignalValue, va_list)> callback) {
    _connections.push_back(SignalConnection(*this, callback));       
}


void Signal::terminate(SignalConnection& connection) {
    auto iter = std::find(_connections.begin(), _connections.end(), connection);
    if(iter != _connections.end()) {
        _connections.erase(iter);
    }
}

