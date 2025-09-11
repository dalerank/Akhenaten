#pragma once

#include <iostream>
#include <ostream>

#include "core/bstring.h"

namespace events_history
{
    constexpr int EVENT_HISTORY_SIZE = 1000;

    struct event_history_record_s
    {
        time_t timestamp;
        std::string name;
        std::string source;
        std::string description;
    };

    struct event_history_s
    {
        int size = EVENT_HISTORY_SIZE;
        std::vector<event_history_record_s> events;
    };
    inline event_history_s event_history;

    inline void _append_record(const event_history_record_s &record)
    {
        event_history.events.push_back(record);
        if (event_history.events.size() > event_history.size)
        {
            event_history.events.erase(event_history.events.begin());
        }
    }

    inline std::string _event_to_string(const event_history_record_s &record)
    {
        const tm *loctime = localtime(&record.timestamp);
        bstring32 timestamp;
        strftime(timestamp, bstring32::capacity, "%FT%TZ", loctime);
        const std::string event_str = std::string(timestamp) + " " + record.name + " " + record.source + " " + record.description;
        return event_str;
    }

    template<typename EventType>
    void log_event (EventType const& ev)
    {
        const char* event_name = typeid(EventType).name();
        // TODO: Replace placeholders with actual source and misc info
        event_history_record_s record = {time(nullptr), event_name, std::string(), std::string()};
        const std::string message = std::string("Event emitted with type: ") + std::string(event_name);
    }

    inline std::vector<std::string> get_history_lines()
    {
        std::vector<std::string> lines;
        lines.reserve(event_history.size);
        for (const auto & event : event_history.events)
        {
            lines.push_back(_event_to_string(event));
        }
        return lines;
    }
}
