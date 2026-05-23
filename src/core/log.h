#pragma once

#include "core/xstring.h"

namespace logs {

void initialize();
void switch_output(pcstr folder);

pcstr output_path();
void flush();

void critical(pcstr format, ...);
void error(pcstr format, ...);
void warn(pcstr format, ...);
void info(pcstr format, ...);
void debug(pcstr format, ...);
void verbose(pcstr format, ...);

} // namespace logs
