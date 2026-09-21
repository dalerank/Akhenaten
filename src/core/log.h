#pragma once

#include "core/core.h"
#include "core/xfunction.h"
#include "core/xstring.h"

namespace logs {

constexpr pcstr default_filename = "akhenaten-log.txt";

using sink_write_fn = xfunction<void(int priority, pcstr prefix, pcstr message)>;
using sink_flush_fn = xfunction<void()>;
using sink_handle = uint32_t;

constexpr sink_handle invalid_sink = 0;

struct file_backend {
    xfunction<bool(pcstr folder, pcstr filename, xstring &out_path)> open;
    xfunction<void()> close;
    xfunction<void(pcstr prefix, pcstr message)> write;
    xfunction<void()> flush;
    xfunction<bool()> has_pending;
};

void initialize();
void switch_output(pcstr folder);

pcstr output_path();
void flush();
void tick();

void set_file_backend(file_backend backend);

using debugger_present_fn = xfunction<bool()>;
void set_debugger_present(debugger_present_fn fn);
bool debugger_present();

sink_handle add_sink(sink_write_fn write, sink_flush_fn flush = {});
void remove_sink(sink_handle handle);

// Last warn/error/critical lines (newest last), for bug reports.
xstring recent_errors(int max_lines = 40);

namespace detail {

void critical_v(pcstr format, ...);
void error_v(pcstr format, ...);
void warn_v(pcstr format, ...);
void info_v(pcstr format, ...);
void debug_v(pcstr format, ...);
void verbose_v(pcstr format, ...);

} // namespace detail

template <typename... Args>
inline void critical(pcstr format, const Args&... args) { detail::critical_v(format, fmt_arg(args)...); }

template <typename... Args>
inline void error(pcstr format, const Args&... args) { detail::error_v(format, fmt_arg(args)...); }

template <typename... Args>
inline void warn(pcstr format, const Args&... args) { detail::warn_v(format, fmt_arg(args)...); }

template <typename... Args>
inline void info(pcstr format, const Args&... args) { detail::info_v(format, fmt_arg(args)...); }

template <typename... Args>
inline void debug(pcstr format, const Args&... args) { detail::debug_v(format, fmt_arg(args)...); }

template <typename... Args>
inline void verbose(pcstr format, const Args&... args) { detail::verbose_v(format, fmt_arg(args)...); }

} // namespace logs
