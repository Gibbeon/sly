/*#include "sly/task.h"
#include "sly/signal.h"
#include "sly/util/thread.h"

using namespace sly;

Task::Task() :    
    Task("_default")
{
    
}

Task::Task(gsl::czstring<> name) :    
    _isLoop(FALSE),
    _receiver(this),
    _name(name),
    _useThread(FALSE)
{
    
}

retval<void> Task::init(        std::string name,
                                std::function<void()>&& runFn) {
    _isLoop     = loop;
    _command    = runFn;
    _name       = name;
    _useThread  = useThread;

    if(_useThread) {
        _thread = std::thread([&]() { Task::run(*this); });
        //if(self._useThread) {
        //    sly::Thread::setName(self._name.c_str());
        //}
    }

    _receiver.init([](SignalReceiver& self, SignalValue value, va_list args) {
        processSignals(self.parent<Task>(), value, args);
    });
    
    return success();
}

SignalReceiver& Task::receiver() {
    return _receiver;
}

void Task::wait() {
    Ensures(!_isLoop); // cannot wait on something that loops forever

    if(!_useThread) {
        while(isIdle) {
            std::this_thread::yield();
        }
    } else {
        ::std::unique_lock lock(_mutex);
        _idle.wait(lock, [&]{ return isIdle(); });
    }
}

void Task::start() {
    if(_useThread) {
        {
            ::std::unique_lock lock(_mutex);
            setState(eTaskState_Running);
        }
        _ready.notify_one();
    } else {
        setState(eTaskState_Running);
        Task::run(*this);
    }
}

void Task::stop() {    
    setState(eTaskState_Stopped);
}

bool_t Task::isIdle() {
    return _state == eTaskState_Idle;
}

bool_t Task::isRunning() {
    return _state == eTaskState_Running;

}

bool_t Task::isStopped() {
    return _state == eTaskState_Stopped;
}

bool_t Task::isLooping() {
    return _isLoop;    
}

bool_t Task::isThreaded() {
    return _useThread;    
}

void Task::setState(eTaskState state) {
    _state = state;
}

void Task::execute() {
    _command();

    if(!isLooping()) {
        setState(eTaskState_Idle);
        if(isThreaded()) {                
            _idle.notify_one();
        }  
    }    
}

void Task::run(Task& self) {  
    do {
        if(self.isThreaded() && self.isIdle()) { 
            std::unique_lock lock(self._mutex);
            self._ready.wait(lock, [&]{ return self.isRunning(); });
        } 
        
        if(self.isRunning()) {
            self.execute();
        } else {
            std::this_thread::yield();
        }    
    } while(self.isLooping() || self.isThreaded());
}

void Task::processSignals(Task& self, SignalValue value, va_list args) {
    switch(value) {
        case eTaskSignal_Start:
            self.start(); 
            break;   
        default:
            S_LOG_ERROR("Invalid signal. %i", value);
            break;
    }
}
*/




