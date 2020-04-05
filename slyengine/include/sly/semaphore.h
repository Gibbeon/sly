#include <mutex>
#include <condition_variable>

#include "sly/global.h"

namespace sly {
    class Semaphore {
    public:
        Semaphore() :  _count(0) {


        }
        
        void notify() {
            std::lock_guard<decltype(_mutex)> lock(_mutex);
            ++_count;

            if(_count > 1) LOG_DEBUG("notify _count on a semaphore was greater than 1. %i", _count);
            
            _condition.notify_one();
        }

        void notifyOne() {
            notify();
        }

        void wait() {
            std::unique_lock<decltype(_mutex)> lock(_mutex);
            while(!_count) { // Handle spurious wake-ups.
                _condition.wait(lock);
                
                if(_count) LOG_DEBUG("wait _count on a semaphore was greater than 1. %i", _count);
            }
            
            _count = MAX(0, _count - 1);
        }

        bool try_wait() {
            std::lock_guard<decltype(_mutex)> lock(_mutex);
            if(_count) {
                --_count;
                return true;
            }
            return false;
        }
        
    private:
        std::mutex              _mutex;
        std::condition_variable _condition;
        size_t                  _count;
    };
}