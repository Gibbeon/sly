#include "sly/debug/logconfig.h"
#include "sly/debug/logwriter.h"
#include "sly/debug/logformatter.h"
#include "sly/debug/streams/clogstream.h"

using namespace sly;

retval<void> LogConfig::configureWriter(LogWriter& writer) {
    writer.init(new CLogStream());
    return success();
}

retval<void> LogConfig::configureFormatter(LogFormatter& formatter) {
    formatter.init();
    return success();
}