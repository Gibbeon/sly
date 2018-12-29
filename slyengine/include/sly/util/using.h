#pragma once

#include "sly/global.h"
#include "sly/disposable.h"

namespace sly {
    class Using {
    public:
        Using(IDisposable& disposable);
        ~Using();

    private:
        IDisposable& disposable_;
    };
}