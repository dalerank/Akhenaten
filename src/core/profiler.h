#pragma once

#include "tracy/Tracy.hpp"
#define OZZY_PROFILER_BEGIN ZoneScoped
#define OZZY_PROFILER_FRAME(x) FrameMark
#define OZZY_PROFILER_SECTION(x) ZoneScopedN(x)
#define OZZY_PROFILER_TAG(y, x) ZoneText(x, strlen(x))
#define OZZY_PROFILER_LOG(text, size) TracyMessage(text, size)
#define OZZY_PROFILER_VALUE(text, value) TracyPlot(text, value)