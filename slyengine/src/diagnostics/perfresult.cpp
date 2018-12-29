#include "sly/diagnostics/perfresult.h"
#include <stdio.h>

using namespace sly;

PerfResult::PerfResult()
{

}

void PerfResult::print()
{
    printf(name.ptr());printf("\n");
    #pragma warning( disable : 4477 )
    printf("\titer=%d min=%dms, max=%dms, avg=%0.2fms, stddev=%0.2fms",avg.count(), *min, *max, *avg, variance.isDefined() ? variance.stddev() : 0.0);
    printf("\n");    
    #pragma warning( default : 4477 )
}