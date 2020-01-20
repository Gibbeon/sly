#include <mutex>
#include <condition_variable>

#include "sly/global.h"

namespace sly {
    class Semaphore {
    public:
        Semaphore() : _count(0) {

        }

        void notify() {
            std::lock_guard<decltype(_mutex)> lock(_mutex);
            ++_count;
            _condition.notify_one();
        }

        void wait() {
            std::unique_lock<decltype(_mutex)> lock(_mutex);
            while(!_count) // Handle spurious wake-ups.
                _condition.wait(lock);
            --_count;
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