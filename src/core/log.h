#pragma once

#include "core/xstring.h"

namespace logs {

void initialize();
void switch_output(pcstr folder);

pcstr output_path();
void flush();

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
