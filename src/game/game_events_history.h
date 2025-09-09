#pragma once

#include <iostream>
#include <ostream>

#include "core/event.h"

namespace events_history
{
    inline void _log_event_to_console(char const* message)
    {
        std::cout << message << std::endl;
    }

    inline void log_permanent_event (const game_event &event)
    {
        const char* event_name = event.name;
        char const* message = (std::string("Permanent event happened with name: ") + std::string(event_name)).c_str();
        _log_event_to_console(message);
    }
}
