#include "qconsole.h"

#include "game/game_events_history.h"

void dev::qconsole::eventsHistory(std::ostream &os) const {
    os << "\nEvents history:";

    const auto &lines = events_history::get_event_history();
    for (int i = 0; i < lines.events.size(); ++i) {
        os << events_history::_event_to_string(lines.events[i]).c_str() << std::endl;
    }

    os << std::endl;
}