#pragma once

#include <thread>

#include "sly/global.h"
#include "sly/task.h"


namespace sly {
    class TaskPool {
    public:
        TaskPool(size_t capacity = 10) :
            _capacity(capacity),
            _active(0),
            _current(0) {

        }

        template<typename Function, typename ...Args> 
        void run(Function fn, Args... args);

        void wait() {
            std::unique_lock lock(_mutex);
            _wait.wait(lock, [&]() { return _current > _tasks.size(); });
        }

    protected:
        void complete(Task<>& task) {
            _active--;
            next();
        }

        void next() {
            std::unique_lock lock(_mutex);
            if(_active < _capacity) {
                _current++;
                if(_current < _tasks.size()) {                    
                    _active++;
                    _tasks[_current].run();
                } else {
                    _wait.notify_one();
                }
            }
        }

        size_t                  _active;
        size_t                  _capacity;
        size_t                  _current;

        std::vector<Task<>>     _tasks;
        std::mutex              _mutex;
        std::condition_variable _wait;
    };

    template<typename Function, typename ...Args> 
    void TaskPool::run(Function function, Args... args) {
        auto& ref = _tasks.emplace_back(Task<>);
        ref.init(
            std::to_string(_tasks.size()), 
            [&]() {      
                function(std::forward<Args>(args)...);
                *this.complete(ref);
            }
        );
        
        next();
    }
}


