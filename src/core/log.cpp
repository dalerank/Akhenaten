#include "core/log.h"

#include "platform/platform.h"
#include "core/app.h"
#include "widget/debug_console.h"

#include <SDL.h>
#include <SDL_log.h>

#include <algorithm>
#include <array>
#include <cstdarg>
#include <cstdio>
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
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
#include "content/content.h"
#include "platform/android/android.h"
#endif

namespace logs {

namespace detail {

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

pcstr prefix_of(SDL_LogPriority priority) {
    priority = (SDL_LogPriority)std::clamp<int>(priority, 0, SDL_NUM_LOG_PRIORITIES);
    return PRIORITY_PREFIX[priority];
}

SDL_LogPriority env_log_priority() {
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

} // namespace detail

class Logger {
public:
    static Logger &instance() {
        static Logger logger;
        return logger;
    }

    static void sdl_write(void * /*userdata*/, int /*category*/, SDL_LogPriority priority, pcstr message) {
        instance().handle_message(priority, message);
    }

    void initialize() {
        SDL_LogSetOutputFunction(sdl_write, nullptr);
        SDL_LogSetAllPriority(detail::env_log_priority());

        setvbuf(stdout, nullptr, _IOFBF, k_stdio_buf_size);
        setvbuf(stderr, nullptr, _IOFBF, k_stdio_buf_size);
        console_out_buf_.reserve(k_console_buf_flush);
        last_flush_ms_ = SDL_GetTicks();
#if defined(GAME_PLATFORM_WIN)
        debug_string_buf_.reserve(k_console_buf_flush);
        SetConsoleOutputCP(CP_UTF8);
        if (IsDebuggerPresent()) {
            return;
        }
#endif

#if !(defined(GAME_PLATFORM_UNIX) && !defined(GAME_PLATFORM_WIN64) && !defined(ANDROID_BUILD))
        signal(SIGSEGV, detail::sig_handler);
#endif
        signal(SIGABRT, detail::sig_handler);
    }

    void switch_output(pcstr folder) {
        flush();
#if defined(GAME_PLATFORM_ANDROID)
        (void)folder;
        if (logger_file_) {
            fclose(logger_file_);
            logger_file_ = nullptr;
        }
        file_stream_.close();
        active_path_ = k_filename;
        vfs::platform_file_manager_remove_file(k_filename);
        logger_file_ = vfs::platform_file_manager_open_file(k_filename, "w");
        if (!logger_file_) {
            __android_log_print(ANDROID_LOG_WARN, "ank-and", "Failed to open log file: %s", k_filename);
            return;
        }
        write_bom_android_();
#else
        file_stream_.close();

        bstring256 filename(folder, "/", k_filename);
        active_path_ = filename.c_str();
        file_stream_.open(filename, std::fstream::out | std::fstream::trunc | std::fstream::binary);
        if (file_stream_.is_open()) {
            write_bom_();
        }
#endif
    }

    pcstr output_path() const {
        return active_path_.c_str();
    }

    void flush() {
        flush_console_out_();
#if defined(GAME_PLATFORM_WIN)
        flush_debug_string_();
#endif
#if defined(GAME_PLATFORM_ANDROID)
        if (logger_file_) {
            fflush(logger_file_);
        }
#else
        if (file_stream_.is_open()) {
            file_stream_.flush();
        }
#endif
        file_dirty_ = false;
        last_flush_ms_ = SDL_GetTicks();
    }

    void tick() {
        if (!has_pending_output_()) {
            return;
        }
        const Uint32 now = SDL_GetTicks();
        if ((now - last_flush_ms_) < k_flush_interval_ms) {
            return;
        }
        flush();
    }

    xstring recent_errors(int max_lines) const {
        if (max_lines <= 0 || recent_errors_count_ == 0) {
            return xstring();
        }
        const size_t n = (std::min)((size_t)max_lines, recent_errors_count_);
        size_t start = (recent_errors_next_ + k_recent_cap - n) % k_recent_cap;
        std::string out;
        out.reserve(n * 96);
        for (size_t i = 0; i < n; ++i) {
            if (i) {
                out += '\n';
            }
            out += recent_errors_[(start + i) % k_recent_cap];
        }
        return xstring(out.c_str());
    }

private:
    static constexpr pcstr k_filename = "akhenaten-log.txt";
    static constexpr size_t k_recent_cap = 64;
    static constexpr size_t k_recent_line_max = 512;
    static constexpr size_t k_console_buf_flush = 8 * 1024;
    static constexpr size_t k_stdio_buf_size = 64 * 1024;
    static constexpr Uint32 k_flush_interval_ms = 1000;

    Logger()
      : active_path_(k_filename) {
#if !defined(GAME_PLATFORM_ANDROID)
        file_stream_.open(k_filename, std::fstream::out | std::fstream::trunc | std::fstream::binary);
        if (file_stream_.is_open()) {
            write_bom_();
        }
#endif
    }

    ~Logger() {
        flush_console_out_();
#if defined(GAME_PLATFORM_WIN)
        flush_debug_string_();
#endif
#if defined(GAME_PLATFORM_ANDROID)
        if (logger_file_) {
            fclose(logger_file_);
            logger_file_ = nullptr;
        }
#else
        file_stream_.close();
#endif
    }

    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;

    void handle_message(SDL_LogPriority priority, pcstr message) {
        pcstr prefix = detail::prefix_of(priority);

        if (priority >= SDL_LOG_PRIORITY_WARN) {
            push_recent_error_(prefix, message);
        }

        write_to_console_(prefix, message);
        write_sinks_(prefix, message);

        if (priority >= SDL_LOG_PRIORITY_WARN) {
            flush();
        } else {
            tick();
        }
    }

    void push_recent_error_(pcstr prefix, pcstr message) {
        std::string line;
        line.reserve(k_recent_line_max);
        if (prefix && *prefix) {
            line += prefix;
        }
        if (message) {
            line += message;
        }
        if (line.size() > k_recent_line_max) {
            line.resize(k_recent_line_max);
        }
        recent_errors_[recent_errors_next_] = std::move(line);
        recent_errors_next_ = (recent_errors_next_ + 1) % k_recent_cap;
        if (recent_errors_count_ < k_recent_cap) {
            ++recent_errors_count_;
        }
    }

    void write_to_console_(pcstr prefix, pcstr message) {
        console_out_buf_ += prefix;
        console_out_buf_ += message;
        console_out_buf_ += '\n';
        if (console_out_buf_.size() >= k_console_buf_flush) {
            flush_console_out_();
        }
    }

    void write_sinks_(pcstr prefix, pcstr message) {
#if defined(GAME_PLATFORM_ANDROID)
        if (logger_file_) {
            fprintf(logger_file_, "%s%s\n", prefix, message);
            file_dirty_ = true;
        }
        __android_log_print(ANDROID_LOG_INFO, "ank-and", "%s%s", prefix, message);
        android_append_startup_log(message);
#else
        if (file_stream_.is_open()) {
            file_stream_ << prefix << message << '\n';
            file_dirty_ = true;
        }

#if defined(GAME_PLATFORM_WIN)
        debug_string_buf_ += prefix;
        debug_string_buf_ += message;
        debug_string_buf_ += '\n';
        if (debug_string_buf_.size() >= k_console_buf_flush) {
            flush_debug_string_();
        }
#endif

        game_debug_cli_message(message);
#endif
    }

    void flush_console_out_() {
        if (console_out_buf_.empty()) {
            return;
        }
        std::cout.write(console_out_buf_.data(), (std::streamsize)console_out_buf_.size());
        std::cout.flush();
        console_out_buf_.clear();
    }

#if defined(GAME_PLATFORM_WIN)
    void flush_debug_string_() {
        if (debug_string_buf_.empty()) {
            return;
        }
        OutputDebugStringA(debug_string_buf_.c_str());
        debug_string_buf_.clear();
    }
#endif

    bool has_pending_output_() const {
        if (!console_out_buf_.empty()) {
            return true;
        }
#if defined(GAME_PLATFORM_WIN)
        if (!debug_string_buf_.empty()) {
            return true;
        }
#endif
        return file_dirty_;
    }

    void write_bom_() {
        const unsigned char bom[] = {0xEF, 0xBB, 0xBF};
        file_stream_.write(reinterpret_cast<const char *>(bom), sizeof(bom));
    }

#if defined(GAME_PLATFORM_ANDROID)
    void write_bom_android_() {
        const unsigned char bom[] = {0xEF, 0xBB, 0xBF};
        fwrite(bom, 1, sizeof(bom), logger_file_);
        fflush(logger_file_);
    }
#endif

    xstring active_path_;
    std::fstream file_stream_;
#if defined(GAME_PLATFORM_ANDROID)
    FILE *logger_file_ = nullptr;
#endif
    std::array<std::string, k_recent_cap> recent_errors_{};
    size_t recent_errors_count_ = 0;
    size_t recent_errors_next_ = 0;
    std::string console_out_buf_;
#if defined(GAME_PLATFORM_WIN)
    std::string debug_string_buf_;
#endif
    Uint32 last_flush_ms_ = 0;
    bool file_dirty_ = false;
};

void initialize() {
    Logger::instance().initialize();
}

void switch_output(pcstr folder) {
    Logger::instance().switch_output(folder);
}

pcstr output_path() {
    return Logger::instance().output_path();
}

void flush() {
    Logger::instance().flush();
}

void tick() {
    Logger::instance().tick();
}

xstring recent_errors(int max_lines) {
    return Logger::instance().recent_errors(max_lines);
}

namespace detail {

void critical_v(pcstr format, ...) {
    if (!format) {
        format = "empty";
    }
    va_list args;
    va_start(args, format);
    log_v(SDL_LOG_PRIORITY_CRITICAL, format, args);
    va_end(args);
}

void error_v(pcstr format, ...) {
    if (!format) {
        format = "empty";
    }
    va_list args;
    va_start(args, format);
    log_v(SDL_LOG_PRIORITY_ERROR, format, args);
    va_end(args);
}

void warn_v(pcstr format, ...) {
    if (!format) {
        format = "empty";
    }
    va_list args;
    va_start(args, format);
    log_v(SDL_LOG_PRIORITY_WARN, format, args);
    va_end(args);
}

void info_v(pcstr format, ...) {
    if (!format) {
        format = "empty";
    }
    va_list args;
    va_start(args, format);
    log_v(SDL_LOG_PRIORITY_INFO, format, args);
    va_end(args);
}

void debug_v(pcstr format, ...) {
    if (!format) {
        format = "empty";
    }
    va_list args;
    va_start(args, format);
    log_v(SDL_LOG_PRIORITY_DEBUG, format, args);
    va_end(args);
}

void verbose_v(pcstr format, ...) {
    if (!format) {
        format = "empty";
    }
    va_list args;
    va_start(args, format);
    log_v(SDL_LOG_PRIORITY_VERBOSE, format, args);
    va_end(args);
}

} // namespace detail

} // namespace logs
