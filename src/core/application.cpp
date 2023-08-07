#include "application.h"

#include "io/log.h"
#include "platform/screen.h"

#include <exception>


namespace app {

void terminate(std::string_view message) noexcept {
    logs::critical(message.data());
    platform_screen_show_error_message_box("CRASHED", message.data());

    std::terminate();
}

} // namespace app