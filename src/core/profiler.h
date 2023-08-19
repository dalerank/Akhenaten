#pragma once

#ifndef TRACY_ENABLE

#define OZZY_PROFILER_BEGIN
#define OZZY_PROFILER_FRAME(x)
#define OZZY_PROFILER_SECTION(x)
#define OZZY_PROFILER_TAG(y, x)
#define OZZY_PROFILER_LOG(text, size)
#define OZZY_PROFILER_VALUE(text, value)

#else

#include "tracy/Tracy.hpp"

#define OZZY_PROFILER_BEGIN ZoneScoped
#define OZZY_PROFILER_FRAME(x) FrameMark
#define OZZY_PROFILER_SECTION(x) ZoneScopedN(x)
#define OZZY_PROFILER_TAG(y, x) ZoneText(x, strlen(x))
#define OZZY_PROFILER_LOG(text, size) TracyMessage(text, size)
#define OZZY_PROFILER_VALUE(text, value) TracyPlot(text, value)

#endif
