#pragma once

#include "core/xstring.h"

namespace snd {
    struct mission_config {
        xstring briefing;
        xstring won;
    };

    mission_config get_mission_config(int mission);
}