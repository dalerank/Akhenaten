#include "core/log.h"

#include "platform/platform.h"
#include "core/app.h"
#include "widget/debug_console.h"

#include <SDL_log.h>

#include <algorithm>
#include <cstdarg>
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <core/flat_map.h>

#ifdef CPPTRACE_ENABLED
#include <cpptrace/cpptrace.hpp>

#include <iomanip>
#include <sstream>
#endif // CPPTRACE_ENABLED

#if defined(GAME_PLATFORM_WIN)
#include <Windows.h>
#include <crtdbg.h>
#elif defined(GAME_PLATFORM_ANDROID)
#include <android/log.h>
#endif

namespace logs {

pcstr logger_filename_ = "akhenaten-log.txt";
static std::fstream logger_file_stream_;
static xstring logger_active_path_ = logger_filename_;

const flat_map<xstring, SDL_LogPriority, 8> PRIORITY_DICT = {
    {"verbose", SDL_LOG_PRIORITY_VERBOSE},
    {"debug", SDL_LOG_PRIORITY_DEBUG},
    {"info", SDL_LOG_PRIORITY_INFO},
    {"warn", SDL_LOG_PRIORITY_WARN},
    {"error", SDL_LOG_PRIORITY_ERROR},
    {"critical", SDL_LOG_PRIORITY_CRITICAL}
};

const std::array<pcstr, 8> PRIORITY_PREFIX = {
    /* SDL_LOG_PRIORITY_NONE, 0 */ "",
    /* SDL_LOG_PRIORITY_VERBOSE, 1 */ "",
    /* SDL_LOG_PRIORITY_DEBUG, 2 */ "debug: ",
    /* SDL_LOG_PRIORITY_INFO, 3 */ "",
    /* SDL_LOG_PRIORITY_WARN, 4 */ "warn: ",
    /* SDL_LOG_PRIORITY_ERROR, 5 */ "error: ",
    /* SDL_LOG_PRIORITY_CRITICAL, 6 */ "critical: ",
    /* SDL_NUM_LOG_PRIORITIES, 7 */ "unknown: ",
};

pcstr get_prefix_of(SDL_LogPriority priority) {
    int ridx = std::clamp<int>(priority, 0, SDL_NUM_LOG_PRIORITIES);
    return PRIORITY_PREFIX[priority];
}

SDL_LogPriority get_log_priority() {
    pcstr env_str = std::getenv("SDL_LOG_PRIORITY");
    xstring priority_str = xstring(env_str ? env_str : "").tolower();
    if (priority_str.empty()) {
        return SDL_LOG_PRIORITY_INFO;
    }

    auto it = PRIORITY_DICT.find(priority_str);
    if (it != PRIORITY_DICT.end()) {
        return it->second;
    }

    std::cerr << "Unknown SDL_LOG_PRIORITY value, VERBOSE will be used" << std::endl;
    return SDL_LOG_PRIORITY_VERBOSE;
 
}

void sig_handler(int signal_num) {
#if defined(GAME_PLATFORM_WIN)
    // SIGABRT обрабатывается отдельным обработчиком под отладчиком
    if (signal_num == SIGABRT && IsDebuggerPresent()) {
        return;
    }
#endif

#ifdef CPPTRACE_ENABLED
    auto const trace = cpptrace::generate_trace();
    std::ostringstream output_stream;
    trace.print_with_snippets(output_stream);

    logs::critical("%s", output_stream.str().c_str());
#endif // CPPTRACE_ENABLED
}

void log_v(SDL_LogPriority priority, pcstr format, va_list args) {
    SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, priority, format, args);
}

/// Logger used by SDL to store messages to the file.
class Logger {
public:
    static void write(void* userdata, int category, SDL_LogPriority priority, pcstr message);

private:
    Logger();
    ~Logger();

    void write(pcstr prefix, pcstr message);
    static void write_to_output_(pcstr prefix, pcstr message);
};

void initialize() {
    SDL_LogSetOutputFunction(Logger::write, nullptr);
    SDL_LogSetAllPriority(get_log_priority());

#if defined(GAME_PLATFORM_WIN)
    SetConsoleOutputCP(CP_UTF8);
    if (IsDebuggerPresent()) {
        return;
    }
#endif

#if !(defined(GAME_PLATFORM_UNIX) && !defined(GAME_PLATFORM_WIN64) && !defined(ANDROID_BUILD))
    signal(SIGSEGV, sig_handler);
#endif
    signal(SIGABRT, sig_handler);
}

void switch_output(pcstr folder) {
    logger_file_stream_.close();

    bstring256 filename(folder, "/", logger_filename_);
    logger_active_path_ = filename.c_str();
    logger_file_stream_.open(filename, std::fstream::out | std::fstream::trunc | std::fstream::binary);
    if (logger_file_stream_.is_open()) {
        const unsigned char bom[] = { 0xEF, 0xBB, 0xBF };
        logger_file_stream_.write(reinterpret_cast<const char*>(bom), sizeof(bom));
    }
}

pcstr output_path() {
    return logger_active_path_.c_str();
}

void flush() {
    if (logger_file_stream_.is_open()) {
        logger_file_stream_.flush();
    }
}

void critical(pcstr format, ...) {
    if (!format) {
        format = "empty";
    }
    va_list args;
    va_start(args, format);
    log_v(SDL_LOG_PRIORITY_CRITICAL, format, args);
    va_end(args);
}

void error(pcstr format, ...) {
    if (!format) {
        format = "empty";
    }
    va_list args;
    va_start(args, format);
    log_v(SDL_LOG_PRIORITY_ERROR, format, args);
    va_end(args);
}

void warn(pcstr format, ...) {
    if (!format) {
        format = "empty";
    }
    va_list args;
    va_start(args, format);
    log_v(SDL_LOG_PRIORITY_WARN, format, args);
    va_end(args);
}

void info(pcstr format, ...) {
    if (!format) {
        format = "empty";
    }
    va_list args;
    va_start(args, format);
    log_v(SDL_LOG_PRIORITY_INFO, format, args);
    va_end(args);
}

void debug(pcstr format, ...) {
    if (!format) {
        format = "empty";
    }
    va_list args;
    va_start(args, format);
    log_v(SDL_LOG_PRIORITY_DEBUG, format, args);
    va_end(args);
}

void verbose(pcstr format, ...) {
    if (!format) {
        format = "empty";
    }
    va_list args;
    va_start(args, format);
    log_v(SDL_LOG_PRIORITY_VERBOSE, format, args);
    va_end(args);
}

Logger::Logger() {
    logger_file_stream_.open(logger_filename_, std::fstream::out | std::fstream::trunc | std::fstream::binary);
    if (logger_file_stream_.is_open()) {
        const unsigned char bom[] = { 0xEF, 0xBB, 0xBF };
        logger_file_stream_.write((pcstr)bom, sizeof(bom));
    }
}

Logger::~Logger() {
    logger_file_stream_.close();
}

void Logger::write(void* /* userdata */, int /* category */, SDL_LogPriority priority, pcstr message) {
    static Logger logger;
    pcstr prefix = get_prefix_of(priority);

    write_to_output_(prefix, message);
    logger.write(prefix, message);
}

void Logger::write(pcstr prefix, pcstr message) {
    logger_file_stream_ << prefix << message << std::endl;

#if defined(GAME_PLATFORM_WIN)
    OutputDebugStringA(prefix);
    OutputDebugStringA(message);
    OutputDebugStringA("\n");
#elif defined(GAME_PLATFORM_ANDROID)
    __android_log_print(ANDROID_LOG_INFO, "ank-and", "%s%s", prefix, message);
#endif

    if (!platform.is_android()) {
        game_debug_cli_message(message);
    }
}

void Logger::write_to_output_(pcstr prefix, pcstr message) {
    std::cout << prefix << message << std::endl;
}

} // namespace logs