#pragma once

#include "core/pool.h"
#include "game/game.h"
#include "game/game_events.h"

template<typename T, size_t N>
class mission_permanent_memory_pool : public pool<T, N> {
public:
    mission_permanent_memory_pool() {
        events::subscribe_permanent([this](event_game_mission_pre_load) {
            this->release_all();
        });
    }
};