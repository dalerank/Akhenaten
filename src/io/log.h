#pragma once

#include <SDL_log.h>

#include <fstream>

namespace logs {
/// Initialize SDL logger
void initialize();

// Note: to handle format-security warnings
template <class Arg, class... Args>
static void critical(char const* format, Arg arg, Args... args) {
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, format, arg, args...);
}

static void critical(char const* message) {
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "%s", message);
}

template <class Arg, class... Args>
static void error(char const* format, Arg arg, Args... args) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, format, arg, args...);
}

static void error(char const* message) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", message);
}

template <class Arg, class... Args>
static void warn(char const* format, Arg arg, Args... args) {
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, format, arg, args...);
}

static void warn(char const* message) {
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "%s", message);
}

template <class Arg, class... Args>
static void info(char const* format, Arg arg, Args... args) {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, format, arg, args...);
}

static void info(char const* message) {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s", message);
}

template <class Arg, class... Args>
static void debug(char const* format, Arg arg, Args... args) {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, format, arg, args...);
}

static void debug(char const* message) {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%s", message);
}

template <class Arg, class... Args>
static void verbose(char const* format, Arg arg, Args... args) {
    SDL_LogVerbose(SDL_LOG_CATEGORY_APPLICATION, format, arg, args...);
}

static void verbose(char const* message) {
    SDL_LogVerbose(SDL_LOG_CATEGORY_APPLICATION, "%s", message);
}

} // namespace logs

/// Logger used by SDL to store messages to the file.
class Logger {
public:
    /// Write each record and flush
    static void write(void* userdata, int category, SDL_LogPriority priority, char const* message);

private:
    /// Output file stream (to store logs)
    std::fstream file_stream_;

    Logger();
    ~Logger();

    void write_to_file_(char const* prefix, char const* message);
    static void write_to_output_(char const* prefix, char const* message);
};
