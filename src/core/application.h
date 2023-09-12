#pragma once

#include <string_view>

namespace app {

/// Show critical error and terminate.
[[noreturn]] void terminate(const char* message) noexcept;

} // namespace app
