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
        xstring source;
        xstring description;
    };

    struct event_history_s
    {
        circular_buffer<event_history_record_s, 8> events;
    };
    extern event_history_s event_history;

    inline void _append_record(const event_history_record_s &record)
    {
        event_history.events.write_tail(record);
    }

    inline const bstring1024& _event_to_string(const event_history_record_s &record)
    {
        const tm *loctime = localtime(&record.timestamp);
        bstring32 timestamp;
        strftime(timestamp, bstring32::capacity, "%FT%TZ", loctime);
        static bstring1024 event_str;
        event_str.append(timestamp);
        event_str.append_fmt(" %s", record.name.c_str());
        event_str.append_fmt(" %s", record.source.c_str());
        event_str.append_fmt(" %s", record.description.c_str());
        return event_str;
    }

    template<typename EventType>
    void log_event (EventType const& ev)
    {
        const char* event_name = typeid(EventType).name();
        // TODO: Replace placeholders with actual source and misc info
        const event_history_record_s record = {time(nullptr), event_name, xstring(), xstring()};
        event_history.events.write_tail(record);
    }
}
