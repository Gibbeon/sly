#include "sly/controller.h"
#include "sly/signal.h"

using namespace sly;

Controller::Controller() :    
    Controller("{unknown}")
{
    
}

Controller::Controller(gsl::czstring<> name) :    
    _isLoop(FALSE),
    _state(eControllerState_Stopped),
    _receiver(this),
    _idle("idle"),
    _running("running"),
    _name(name)
{
    
}

retval<void> Controller::init(  std::function<void()>&& runFn, 
                                bool_t loop) {
    _isLoop = loop;
    _command = runFn;

    _thread = std::thread([&]() { Controller::run(*this); });
    _receiver.init([](SignalReceiver& self, SignalValue value, va_list args) {
        processSignals(self.parent<Controller>(), value, args);
    });
    
    return success();
}

void Controller::shutdown() {
    setState(eControllerState_Stopped);
}

bool_t Controller::active() const {
    return _state != eControllerState_Stopped;
}    

eControllerState Controller::state() const {
    return _state;
}

Signal& Controller::signal() {
    return _signal;
}

SignalReceiver& Controller::receiver() {
    return _receiver;
}

void Controller::wait() {
    _idle.wait();
}

void Controller::setState(eControllerState state) {
    _state = state;
}

void Controller::execute() {
    if(_command) {
        _command();
    } 

    if(!_isLoop) {
        setState(eControllerState_Waiting);    
    } // else keep running
}

void Controller::processSignals(Controller& self, SignalValue value, va_list args) {
    switch(value) {
        case SIGNAL_START:
            self.setState(eControllerState_Running);
            self._running.notify();
            break;
    }
}

void Controller::run(Controller& self) {    
    self._running.wait();

    while(true) {
        switch(self.state()) {
            case eControllerState_Running:
                self.execute();
                break;

            case eControllerState_Waiting:
                self._idle.notify();
                self._running.wait();
                break;
            
            case eControllerState_Stopped:
            break;// do nothing, should clean up
        }
    }
}



