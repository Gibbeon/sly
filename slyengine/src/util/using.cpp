#include "sly/global.h"
#include "sly/util/using.h"

using namespace sly;


Using::Using(IDisposable& disposable) :
    disposable_(disposable)
{
    
}

Using::~Using() {
    disposable_.dispose();
}