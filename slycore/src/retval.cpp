#include "sly/retval.h"

sly::retval<void> sly::return_void() {
    return sly::retval<void>();
}