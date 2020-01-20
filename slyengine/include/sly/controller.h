#pragma once

#include <thread>

#include "sly/global.h"
#include "sly/signal.h"
#include "sly/signalreceiver.h"
#include "sly/semaphore.h"


namespace sly {
    ENUM_DECL(eControllerState, 
        eControllerState_Waiting,
        eControllerState_Running,
        eControllerState_Stopped
    );

    class Controller {
    public:
        Controller();
        retval<void> init(          std::function<void()>&& runFn, 
                                    bool_t loop = TRUE);

        void wait();
        void shutdown();

        bool_t active() const;
        eControllerState state() const;
        
        Signal& signal();
        SignalReceiver& receiver();

        static void processSignals(Controller&, SignalValue, va_list); 

    protected:     
        void setState(eControllerState state);

        void execute();
        void idle();
          
        static void run(Controller&) ;

        bool_t                          _isLoop;
        eControllerState                _state;
        std::thread                     _thread;
        Semaphore                       _semaphore;
        std::function<void()>           _command;
        SignalReceiver                  _receiver;
        Signal                          _signal;
    };
}


