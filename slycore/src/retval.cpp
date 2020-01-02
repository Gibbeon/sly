#include "sly/retval.h"

sly::retval<void> sly::make_return() {
    return sly::retval<void>();
}