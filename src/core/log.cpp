#include "core/log.h"

#include "platform/platform.h"
#include "core/core.h"
#include "core/svector.h"

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
#include <utility>
#include <core/flat_map.h>

#ifdef CPPTRACE_ENABLED
#include <cpptrace/cpptrace.hpp>

#include <iomanip>
#include <sstream>
#endif // CPPTRACE_ENABLED

namespace logs {

namespace {

debugger_present_fn g_debugger_present;

} // namespace

bool debugger_present() {
    return g_debugger_present && g_debugger_present();
}

void set_debugger_present(debugger_present_fn fn) {
    g_debugger_present = std::move(fn);
}

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
    if (signal_num == SIGABRT && logs::debugger_present()) {
        return;
    }

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

std::fstream &default_file_stream() {
    static std::fstream stream;
    return stream;
}

bool &default_file_dirty() {
    static bool dirty = false;
    return dirty;
}

file_backend make_default_file_backend() {
    file_backend backend;
    backend.open = [](pcstr folder, pcstr filename, xstring &out_path) -> bool {
        auto &stream = default_file_stream();
        stream.close();

        bstring256 path;
        if (folder && *folder) {
            path = bstring256(folder, "/", filename);
        } else {
            path = filename;
        }
        out_path = path.c_str();
        stream.open(path, std::fstream::out | std::fstream::trunc | std::fstream::binary);
        if (!stream.is_open()) {
            return false;
        }
        const unsigned char bom[] = {0xEF, 0xBB, 0xBF};
        stream.write(reinterpret_cast<const char *>(bom), sizeof(bom));
        default_file_dirty() = false;
        return true;
    };
    backend.close = []() {
        default_file_stream().close();
        default_file_dirty() = false;
    };
    backend.write = [](pcstr prefix, pcstr message) {
        auto &stream = default_file_stream();
        if (!stream.is_open()) {
            return;
        }
        stream << prefix << message << '\n';
        default_file_dirty() = true;
    };
    backend.flush = []() {
        auto &stream = default_file_stream();
        if (stream.is_open()) {
            stream.flush();
        }
        default_file_dirty() = false;
    };
    backend.has_pending = []() {
        return default_file_dirty();
    };
    return backend;
}

} // namespace detail

class Logger {
public:
    struct sink {
        sink_handle handle = invalid_sink;
        sink_write_fn write;
        sink_flush_fn flush;
    };

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

        if (!file_backend_.open) {
            file_backend_ = detail::make_default_file_backend();
        }

        register_default_sinks_();
        open_file_(nullptr);

        if (debugger_present()) {
            return;
        }

        // Desktop Unix: crashhandler_install() already owns SIGSEGV.
        if (!platform.is_unix() || platform.is_android()) {
            signal(SIGSEGV, detail::sig_handler);
        }
        signal(SIGABRT, detail::sig_handler);
    }

    void switch_output(pcstr folder) {
        flush();
        open_file_(folder);
    }

    void set_file_backend(file_backend backend) {
        if (file_backend_.close) {
            file_backend_.close();
        }
        file_backend_ = std::move(backend);
    }

    pcstr output_path() const {
        return active_path_.c_str();
    }

    sink_handle add_sink(sink_write_fn write, sink_flush_fn flush_fn) {
        if (!write || sinks_.full()) {
            return invalid_sink;
        }
        const sink_handle handle = ++next_sink_id_;
        sinks_.push_back(sink{handle, std::move(write), std::move(flush_fn)});
        return handle;
    }

    void remove_sink(sink_handle handle) {
        if (handle == invalid_sink) {
            return;
        }
        for (auto it = sinks_.begin(); it != sinks_.end(); ++it) {
            if (it->handle == handle) {
                sinks_.erase(it);
                return;
            }
        }
    }

    void flush() {
        for (const auto &s : sinks_) {
            if (s.flush) {
                s.flush();
            }
        }
        last_flush_ms_ = SDL_GetTicks();
    }

    void tick() {
        const Uint32 now = SDL_GetTicks();
        if ((now - last_flush_ms_) < k_flush_interval_ms) {
            return;
        }
        flush();
    }

    xstring recent_errors(int max_lines) const {
        return format_ring_(recent_errors_, recent_errors_next_, recent_errors_count_, max_lines);
    }

    xstring recent_log_tail(int max_lines) const {
        return format_ring_(recent_log_, recent_log_next_, recent_log_count_, max_lines);
    }

private:
    static constexpr size_t k_recent_cap = 64;
    static constexpr size_t k_recent_log_cap = 128;
    static constexpr size_t k_recent_line_max = 512;
    static constexpr size_t k_console_buf_flush = 8 * 1024;
    static constexpr size_t k_stdio_buf_size = 64 * 1024;
    static constexpr Uint32 k_flush_interval_ms = 1000;
    static constexpr size_t k_max_sinks = 8;

    template <size_t Cap>
    static xstring format_ring_(const std::array<std::string, Cap> &ring, size_t next, size_t count, int max_lines) {
        if (max_lines <= 0 || count == 0) {
            return xstring();
        }
        const size_t n = (std::min)((size_t)max_lines, count);
        size_t start = (next + Cap - n) % Cap;
        std::string out;
        out.reserve(n * 96);
        for (size_t i = 0; i < n; ++i) {
            if (i) {
                out += '\n';
            }
            out += ring[(start + i) % Cap];
        }
        return xstring(out.c_str());
    }

    Logger()
      : active_path_(default_filename) {
    }

    ~Logger() {
        flush();
        if (file_backend_.close) {
            file_backend_.close();
        }
    }

    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;

    void open_file_(pcstr folder) {
        if (!file_backend_.open) {
            return;
        }
        file_backend_.open(folder, default_filename, active_path_);
    }

    void register_default_sinks_() {
        if (defaults_registered_) {
            return;
        }
        defaults_registered_ = true;

        add_sink(
          [this](int, pcstr prefix, pcstr message) { stdout_write_(prefix, message); },
          [this]() { stdout_flush_(); });
        add_sink(
          [this](int, pcstr prefix, pcstr message) {
              if (file_backend_.write) {
                  file_backend_.write(prefix, message);
              }
          },
          [this]() {
              if (file_backend_.flush) {
                  file_backend_.flush();
              }
          });
    }

    void handle_message(SDL_LogPriority priority, pcstr message) {
        pcstr prefix = detail::prefix_of(priority);

        if (priority >= SDL_LOG_PRIORITY_INFO) {
            push_recent_line_(recent_log_, recent_log_next_, recent_log_count_, prefix, message);
        }
        if (priority >= SDL_LOG_PRIORITY_WARN) {
            push_recent_line_(recent_errors_, recent_errors_next_, recent_errors_count_, prefix, message);
        }

        for (const auto &s : sinks_) {
            s.write((int)priority, prefix, message);
        }

        if (priority >= SDL_LOG_PRIORITY_WARN) {
            flush();
        } else {
            tick();
        }
    }

    template <size_t Cap>
    void push_recent_line_(std::array<std::string, Cap> &ring,
                           size_t &next,
                           size_t &count,
                           pcstr prefix,
                           pcstr message) {
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
        ring[next] = std::move(line);
        next = (next + 1) % Cap;
        if (count < Cap) {
            ++count;
        }
    }

    void stdout_write_(pcstr prefix, pcstr message) {
        console_out_buf_ += prefix;
        console_out_buf_ += message;
        console_out_buf_ += '\n';
        if (console_out_buf_.size() >= k_console_buf_flush) {
            stdout_flush_();
        }
    }

    void stdout_flush_() {
        if (console_out_buf_.empty()) {
            return;
        }
        std::cout.write(console_out_buf_.data(), (std::streamsize)console_out_buf_.size());
        std::cout.flush();
        console_out_buf_.clear();
    }

    xstring active_path_;
    file_backend file_backend_;
    std::array<std::string, k_recent_cap> recent_errors_{};
    size_t recent_errors_count_ = 0;
    size_t recent_errors_next_ = 0;
    std::array<std::string, k_recent_log_cap> recent_log_{};
    size_t recent_log_count_ = 0;
    size_t recent_log_next_ = 0;
    std::string console_out_buf_;
    Uint32 last_flush_ms_ = 0;
    bool defaults_registered_ = false;
    sink_handle next_sink_id_ = invalid_sink;
    svector<sink, k_max_sinks> sinks_;
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

void set_file_backend(file_backend backend) {
    Logger::instance().set_file_backend(std::move(backend));
}

sink_handle add_sink(sink_write_fn write, sink_flush_fn flush_fn) {
    return Logger::instance().add_sink(std::move(write), std::move(flush_fn));
}

void remove_sink(sink_handle handle) {
    Logger::instance().remove_sink(handle);
}

xstring recent_errors(int max_lines) {
    return Logger::instance().recent_errors(max_lines);
}

xstring recent_log_tail(int max_lines) {
    return Logger::instance().recent_log_tail(max_lines);
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
