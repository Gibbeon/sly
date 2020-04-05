#pragma once

#include <thread>

#include "sly/global.h"
#include "sly/signal.h"
#include "sly/signalreceiver.h"


namespace sly {
    ENUM_DECL(eTaskState, 
        eTaskState_Resolved,
        eTaskState_Running,
        eTaskState_Waiting,
        eTaskState_Uninitalized
    );

    ENUM_DECL_OFTYPE(eTaskSignal, SignalValue, 
        eTaskSignal_Start = SIGNAL_START
    );

    template<typename TReturn = void, typename ...TArgs>
    struct TaskDesc {
    public:
        std::string                         name;
        std::function<TReturn(TArgs...)>    command;
    };

    template<typename TReturn>
    class Promise;

    class ITask {
    public:
        virtual ~ITask() {}
        virtual retval<void> wait() = 0;
         
        virtual bool_t isRunning()= 0;
        virtual bool_t isResolved() = 0;

        virtual void setReturnAddr(vptr_t) = 0; 
    protected:
        ITask() {}   

    };

    template<typename TReturn>
    class Promise {
    public:
        Promise(ITask& task) : _task(task), _resolved(FALSE) {
            
        }
        
        Promise(TReturn& value) : _resolved(TRUE), _result(value) {
            
        }

        Promise( Promise const& )              = delete;        
        Promise& operator = ( Promise const& ) = delete;

        Promise( Promise && other ) : _task(other._task) {           
            if(other._resolved) {
                _result = other._result;
                _resolved = true;
            } else {
                _task.setReturnAddr(reinterpret_cast<vptr_t>(&_result)); 
                _resolved = false;  
            }      
        }

        Promise& operator = ( Promise && other ) {
            _task = other._task;           
            if(other._resolved) {
                _result = other._result;
                _resolved = true;
            } else {
                _task.setReturnAddr(&_result); 
                _resolved = false;  
            }       
        }

        operator TReturn& () {
            return resolve();
        }

    private:
        TReturn& resolve() {
            if(!_resolved) {
                _task.wait();
            }

            return _result;
        }

        bool_t                      _resolved;
        TReturn                     _result;
        ITask&                      _task;
        
    };

    template<>
    class Promise<void> {
    public:
        Promise(ITask& task) : _task(task), _resolved(FALSE) {
            
        }

        Promise( Promise const& )              = delete;        
        Promise& operator = ( Promise const& ) = delete;

        Promise( Promise && other ) : _task(other._task) {           
            if(other._resolved) {
                _resolved = true;
            } else {
                _resolved = false;  
            }      
        }

        Promise& operator = ( Promise && other ) {
            _task = other._task;           
            if(other._resolved) {
                _resolved = true;
            } else {
                _resolved = false;  
            }       
        }

    private:
        void resolve() {
            if(!_resolved) {
                _task.wait();
            }
        }

        bool_t                      _resolved;
        ITask&                      _task;
    };



    template<typename TReturn = size_t, typename ...TArgs>
    class Task : public ITask {
    public:
        Task();
        Task(gsl::czstring<> name);
        
        Task( Task const& )              = delete;
        Task( Task && )                  = delete;
        Task& operator = ( Task const& ) = delete;
        Task& operator = ( Task && )     = delete;

        virtual retval<void> init(          std::string name,
                                            std::function<TReturn(TArgs...)>&& command);

        virtual Promise<TReturn>    run(TArgs...);
        virtual retval<TReturn>     runSyncronously(TArgs...);        
        virtual retval<void>        abort();
        virtual retval<void>        wait();

        virtual bool_t isRunning();
        virtual bool_t isResolved();   
        virtual bool_t isStopped();   

    protected:     
        void setState(eTaskState state);
        void execute(TArgs...);
        virtual void setReturnAddr(vptr_t resultAddr) {
            _resultAddr = reinterpret_cast<TReturn*>(resultAddr);
        }
          
        static TReturn run(Task&) ;

        std::thread                      _thread;
        std::function<TReturn(TArgs...)> _command;
        TReturn*                         _resultAddr;
        std::string                      _name;
        std::condition_variable          _ready;
        std::condition_variable          _idle;
        std::mutex                       _mutex;
        eTaskState                       _state;

    public:
        friend class Promise<TReturn>;
    };

    template<typename TReturn, typename ...TArgs>
    Task<TReturn, TArgs...>::Task() : _resultAddr(nullptr), _state(eTaskState_Uninitalized)

    template<typename TReturn, typename ...TArgs>
    Task<TReturn, TArgs...>::Task(  gsl::czstring<> name, 
                                    std::function<TReturn(TArgs...)>&& command) : 
                                    _name(name),
                                    _command(command),
                                    _resultAddr(nullptr), 
                                    _state(eTaskState_Waiting) {}

    template<typename TReturn, typename ...TArgs>
    retval<void> Task<TReturn, TArgs...>::init(     std::string name,
                                                    std::function<TReturn(TArgs...)>&& command) {
        _name = name;
        _command = command;
        setState(eTaskState_Waiting);
    }

    template<typename TReturn, typename ...TArgs>
    Promise<TReturn> Task<TReturn, TArgs...>::run(TArgs...) {
        Promise<TReturn> result(*this);

        _thread = std::thread([&]() {                
                execute();                
                _ready.notify_one();
            }
        );               

        return std::move(result);
    }

    
    template<typename TReturn, typename ...TArgs>
    retval<TReturn> Task<TReturn, TArgs...>::runSyncronously(TArgs...) {
        TReturn result;
        _resultAddr = &result;
        execute();  
        return result;
    }

    /*template<>
    retval<void> Task<void>::runSyncronously() {
        execute();  
        return success();
    }

    template<>
    void Task<void>::execute() {
        _command();
        setState(eTaskState_Resolved);
    }*/

    template<typename TReturn, typename ...TArgs>
    retval<void> Task<TReturn, TArgs...>::abort() {
        if(_thread.joinable()) {
            _thread.join();        
        }    
        setState(eTaskState_Waiting);
        return success();
    }

    template<typename TReturn, typename ...TArgs>
    retval<void> Task<TReturn, TArgs...>::wait() {
        std::unique_lock lock(_mutex);
        _ready.wait(lock, [&]() { return isResolved() || isStopped(); } );
        return success();
    }

    template<typename TReturn, typename ...TArgs>
    bool_t Task<TReturn, TArgs...>::isStopped() {
        return eTaskState_Waiting == _state;
    }


    template<typename TReturn, typename ...TArgs>
    bool_t Task<TReturn, TArgs...>::isRunning() {
        return eTaskState_Running == _state;
    }

    template<typename TReturn, typename ...TArgs>
    bool_t Task<TReturn, TArgs...>::isResolved() {
        return eTaskState_Resolved == _state;
    }

    template<typename TReturn, typename ...TArgs>
    void Task<TReturn, TArgs...>::setState(eTaskState state) {
        _state = state;
    }

    template<typename TReturn, typename ...TArgs>
    void Task<TReturn, TArgs...>::execute(TArgs... args) {
        if(_resultAddr) {
            *_resultAddr = _command(std::forward<TArgs...>(args)...);
        } else {
            _command();
        }
        setState(eTaskState_Resolved);
    }

}



