#pragma once

#include <SDL_log.h>

#include <fstream>

namespace logs {
/// Initialize SDL logger
void initialize();
void switch_output(const char *folder);

// Note: to handle format-security warnings
template <class... Args>
inline void critical(char const* format, Args... args) {
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, format, args...);
}

inline void critical(char const* msg) {
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "%s", msg);
}

template <class... Args>
inline void error(char const* format, Args... args) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, format, args...);
}

inline void error(char const* msg) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", msg);
}

template <class... Args>
inline void warn(char const* format, Args... args) {
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, format, args...);
}

inline void warn(char const* msg) {
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "%s", msg);
}

template <class... Args>
inline void info(char const* format, Args... args) {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, format, args...);
}

inline void info(char const* msg) {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s", msg);
}

template <class... Args>
inline void debug(char const* format, Args... args) {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, format, args...);
}

inline void debug(char const* msg) {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%s", msg);
}

template <class... Args>
inline void verbose(char const* format, Args... args) {
    SDL_LogVerbose(SDL_LOG_CATEGORY_APPLICATION, format, args...);
}

inline void verbose(char const* msg) {
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
