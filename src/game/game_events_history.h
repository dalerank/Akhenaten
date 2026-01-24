#pragma once

#include <iostream>
#include <ostream>

#include "core/xstring.h"
#include "core/circullar_buffer.h"

namespace events_history {
    struct event_history_record_s
    {
        time_t timestamp;
        xstring name;
        xstring description;
        pcstr source;
    };

    struct event_history_s
    {
        circular_buffer<event_history_record_s, 8> events;
    };
        
    const event_history_s& get_event_history();
    event_history_s& ref_event_history();

    void _append_record(const event_history_record_s &record);

    const bstring1024& _event_to_string(const event_history_record_s &record);

    template<typename EventType>
    void log_event (EventType const& ev)
    {
        const char* event_name = typeid(EventType).name();
        // TODO: Replace placeholders with actual source and misc info
        const event_history_record_s record = {time(nullptr), event_name, xstring(), ""};
        ref_event_history().events.write_tail(record);
    }
}
