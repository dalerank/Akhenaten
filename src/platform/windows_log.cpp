#include "platform/platform.h"

#if defined(GAME_PLATFORM_WIN)

#include "core/app.h"
#include "core/log.h"
#include "core/xvalue.h"

#include <Windows.h>

#include <string>
#include <utility>

struct windows_log_t {
    static constexpr size_t k_buf_flush = 8 * 1024;

    ~windows_log_t() {
        flush_debug_string();
        if (ods_sink_ != logs::invalid_sink) {
            logs::remove_sink(ods_sink_);
            ods_sink_ = logs::invalid_sink;
        }
    }

    void install() {
        if (installed_) {
            return;
        }
        installed_ = true;

        logs::set_debugger_present([] { return IsDebuggerPresent() != 0; });

        SetConsoleOutputCP(CP_UTF8);
        debug_string_buf_.reserve(k_buf_flush);

        ods_sink_ = logs::add_sink(
          [](int, pcstr prefix, pcstr message) {
              xvalue<windows_log_t>::ref().write_debug_string(prefix, message);
          },
          []() { xvalue<windows_log_t>::ref().flush_debug_string(); });
    }

    void write_debug_string(pcstr prefix, pcstr message) {
        debug_string_buf_ += prefix;
        debug_string_buf_ += message;
        debug_string_buf_ += '\n';
        if (debug_string_buf_.size() >= k_buf_flush) {
            flush_debug_string();
        }
    }

    void flush_debug_string() {
        if (debug_string_buf_.empty()) {
            return;
        }
        OutputDebugStringA(debug_string_buf_.c_str());
        debug_string_buf_.clear();
    }

    std::string debug_string_buf_;
    bool installed_ = false;
    logs::sink_handle ods_sink_ = logs::invalid_sink;
};

// Signal policy must be available before logs::initialize(); modules register later.
namespace {
struct windows_log_signal_policy_t {
    windows_log_signal_policy_t() {
        logs::set_debugger_present([] { return IsDebuggerPresent() != 0; });
    }
};
windows_log_signal_policy_t g_windows_log_signal_policy;
} // namespace

void ANK_REGISTER_APPLICATION_MODULE(register_windows_log_module) {
    xvalue<windows_log_t>::ref().install();
}

#endif // GAME_PLATFORM_WIN
