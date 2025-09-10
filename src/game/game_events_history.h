#pragma once

#include <iostream>
#include <ostream>

#include "core/event.h"

namespace events_history
{
    inline void _log_event_to_console(std::string const* message)
    {
        std::cout << message->c_str() << std::endl;
    }

    template<typename EventType>
    void log_event (EventType const& ev)
    {

        // const char* event_name = event.name;
        const std::string message = std::string("Event emitted with type: ") + std::string(typeid(EventType).name());
        _log_event_to_console(&message);
    }
}
