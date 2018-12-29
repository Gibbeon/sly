#include "sly/diagnostics/perftest.h"
#include "sly/util/stopwatch.h"

using namespace sly;

PerfTest::PerfTest(s32 iterations, s32 skip) :
    iterations_(iterations),
    skip_(skip)
{
    SLYASSERT_GT(iterations_, 0, "PerfTest iterations must be greater than 0.");
    SLYASSERT_GE(skip_, 0, "PerfTest skip value must be greater or equal to 0.");
}

void PerfTest::add(String<> name, Function<void()> function)
{
    functions_.add(name, function);
}

List<PerfResult> PerfTest::run()
{
    List<PerfResult> results;
    functions_.foreach([&](Pair<String<>, Function<void()>> test){
        PerfResult result;
        result.name = test.key;

        for(s32 i = 0; i < iterations_ + skip_; i++)
        {            
            Stopwatch sw;
        
            sw.start();
            test.value();
            sw.stop();

            if(i >= skip_)
            {
                result.min += sw.elapsed().getNanoseconds() / 1000;
                result.max += sw.elapsed().getNanoseconds() / 1000;
                result.avg += (double)sw.elapsed().getNanoseconds() / 1000;
                result.variance += (double)sw.elapsed().getNanoseconds() / 1000;
            }
        }
        
        results.add(result);
    });

    return results;
}
