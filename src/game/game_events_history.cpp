#include "game_events_history.h"

events_history::event_history_s event_history;
const events_history::event_history_s& events_history::get_event_history() {
    return event_history;
}
events_history::event_history_s& events_history::ref_event_history() {
    return event_history;
}

void events_history::_append_record(const event_history_record_s &record) {
    event_history.events.write_tail(record);
}

const bstring1024 &events_history::_event_to_string(const event_history_record_s &record) {
    const tm *loctime = localtime(&record.timestamp);
    bstring32 timestamp;
    strftime(timestamp, bstring32::capacity, "%FT%TZ", loctime);
    static bstring1024 event_str;
    event_str.append(timestamp);
    event_str.append_fmt(" %s", record.name.c_str());
    event_str.append_fmt(" %s", record.description.c_str());
    event_str.append_fmt(" %s", record.source);
    return event_str;
}
