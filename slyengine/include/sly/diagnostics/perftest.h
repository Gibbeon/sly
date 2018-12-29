#pragma once

#include "sly/global.h"
#include "sly/string.h"
#include "sly/collections/list.h"
#include "sly/collections/map.h"
#include "sly/diagnostics/perfresult.h"

namespace sly {
    class PerfTest
    {
        public:
            PerfTest(s32 iterations = 10, s32 skip = 0);

            void add(String<> name, Function<void()> function);

            List<PerfResult> run();

            void printAll();

        private:
            Map<String<>, Function<void()>> functions_;
            s32 iterations_, skip_;
    };

}