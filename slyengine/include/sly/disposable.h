#pragma once

#include "sly/global.h"

class IDisposable {
public:
    virtual void dispose() = 0;    
};