#include "application.h"

#include "core/log.h"
#include "platform/screen.h"

namespace app {

void terminate(const char* message) noexcept {
    logs::critical("%s", message);
    platform_screen_show_error_message_box("CRASHED", message);

    std::terminate();
}

} // namespace app
