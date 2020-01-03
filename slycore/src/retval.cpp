#include "sly/retval.h"

sly::retval<void> sly::success() {
    return sly::retval<void>();
}