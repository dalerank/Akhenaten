#include "game/game_events.h"

#include <vector>

static std::vector<void (*)()>& session_subscribers() {
    static std::vector<void (*)()> s;
    return s;
}

events::session_subscriber::session_subscriber(void (*subscribe)()) {
    session_subscribers().push_back(subscribe);
}

void events::start_session() {
    g_city_events.removeListeners();
    for (auto subscribe : session_subscribers()) {
        subscribe();
    }
}
