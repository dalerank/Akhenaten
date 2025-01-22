#pragma once

#include <SDL_log.h>

#include <fstream>
#include "core/xstring.h"

namespace logs {
/// Initialize SDL logger
void initialize();
void switch_output(pcstr folder);

// Note: to handle format-security warnings
template <class... Args>
inline void critical(pcstr format, Args... args) {
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, format, args...);
}

inline void critical(pcstr msg) {
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "%s", msg);
}

template <class... Args>
inline void error(pcstr format, Args... args) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, format, args...);
}

inline void error(pcstr msg) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", msg);
}

template <class... Args>
inline void warn(pcstr format, Args... args) {
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, format, args...);
}

inline void warn(pcstr msg) {
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "%s", msg);
}

template <class... Args>
inline void info(pcstr format, Args... args) {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, format, args...);
}

inline void info(pcstr msg) {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s", msg);
}

template <class... Args>
inline void debug(pcstr format, Args... args) {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, format, args...);
}

inline void debug(pcstr msg) {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%s", msg);
}

template <class... Args>
inline void verbose(pcstr format, Args... args) {
    SDL_LogVerbose(SDL_LOG_CATEGORY_APPLICATION, format, args...);
}

inline void verbose(pcstr msg) {
    SDL_LogVerbose(SDL_LOG_CATEGORY_APPLICATION, "%s", msg);
}

} // namespace logs

/// Logger used by SDL to store messages to the file.
class Logger {
public:
    /// Write each record and flush
    static void write(void* userdata, int category, SDL_LogPriority priority, char const* message);

private:
    Logger();
    ~Logger();

    void write_to_file_(char const* prefix, char const* message);
    static void write_to_output_(char const* prefix, char const* message);
};
