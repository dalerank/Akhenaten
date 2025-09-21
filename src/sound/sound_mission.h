#pragma once

#include "core/archive.h"
#include <type_traits>

namespace snd {
    struct mission_config {
        int mission;
        xstring briefing;
        xstring won;
        bool operator==(const mission_config &other) const noexcept { return mission == other.mission; }
        bool operator!=(const mission_config &other) const noexcept { return mission != other.mission; }
        bool operator<(const mission_config &other) const noexcept { return mission < other.mission; }
    };

    mission_config get_mission_config(int mission);
}

template<>
struct std::hash<snd::mission_config> {
    std::size_t operator()(const snd::mission_config &k) const noexcept {
        return k.mission;
    }
};

ANK_CONFIG_STRUCT(snd::mission_config, mission, briefing, won)