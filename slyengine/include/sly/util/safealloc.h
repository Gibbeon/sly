#pragma once

#include "sly/global.h"

    namespace sly {

    template <typename T>
    class SafeAlloc {
        public:
            template <typename TArgs...>
            SafeAlloc(TArgs... args);
            SafeAlloc(u32 length);
            SafeAlloc(T* ptr);
            ~SafeAlloc();

            T* ptr() const;
            operator T*() const;
            T& operator*() const;

        private:
            T* ptr_;
    };


    #include "sly/util/safealloc.hpp"

}
