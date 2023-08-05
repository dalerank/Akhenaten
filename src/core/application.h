#pragma once

#include <string_view>

namespace app {

/// Show critical error and terminate.
[[noreturn]] void terminate(std::string_view message) noexcept;

} // namespace app
