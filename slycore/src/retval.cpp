#include "sly/retval.h"

sly::retval<void> sly::success() {
    return sly::retval<void>();
}

sly::retval<void> sly::failed() {
    return sly::retval<void>();
}