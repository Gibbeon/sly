#include "sly/signalreceiver.h"

using namespace sly;

void SignalReceiver::accept(SignalValue value, va_list args) {
    Ensures(_handler);
    _handler(*this, value, args);
}

void SignalReceiver::connect(SignalConnection& connection) {
    _connections.push_back(&connection);
}

void SignalReceiver::terminate(SignalConnection& connection) {
    std::remove(_connections.begin(), _connections.end(), &connection);
}

