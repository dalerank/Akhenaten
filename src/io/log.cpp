#include "io/log.h"
#include "SDL.h"

#include <stdio.h>

#ifdef _MSC_VER
#include "windows.h"
#endif

#define MSG_SIZE 1000

static char log_buffer[MSG_SIZE];

void log_info(const char* msg, ...) {
    va_list valist;
    va_start(valist, msg);

    vsnprintf(log_buffer, 1000, msg, valist);

    va_end(valist);

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s", log_buffer);

#ifdef _MSC_VER
    OutputDebugStringA(log_buffer);
    OutputDebugStringA("\n");
#endif
}

void log_error(const char* msg, ...) {
    va_list valist;
    va_start(valist, msg);

    vsnprintf(log_buffer, 1000, msg, valist);

    va_end(valist);

    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", log_buffer);

#ifdef _MSC_VER
    OutputDebugStringA(log_buffer);
    OutputDebugStringA("\n");
#endif
}
