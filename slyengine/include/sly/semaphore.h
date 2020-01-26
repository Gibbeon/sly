#include <mutex>
#include <condition_variable>

#include "sly/global.h"

namespace sly {
    class Semaphore {
    public:
        Semaphore() : _name("unknown"), _count(0) {


        }
        
        Semaphore(gsl::czstring<> name) : _name(name), _count(0) {

        }

        void notify() {
            std::lock_guard<decltype(_mutex)> lock(_mutex);
            ++_count;
            
            //LOG_VERBOSE("%s notify() -- _count %i", _name, _count);
            _condition.notify_one();
        }

        void wait() {
            std::unique_lock<decltype(_mutex)> lock(_mutex);
            //LOG_VERBOSE("%s sleep() _count %i", _name, _count);
            while(!_count) { // Handle spurious wake-ups.
                //LOG_VERBOSE("%s waitFor() -- _count %i", _name, _count);
                _condition.wait(lock);
                //LOG_VERBOSE("%s notice() -- _count %i", _name, _count);
            }
            
            --_count;
            //LOG_VERBOSE("%s wake() _count %i", _name, _count);
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
        const char* _name;
        std::mutex              _mutex;
        std::condition_variable _condition;
        size_t                  _count;
    };
}