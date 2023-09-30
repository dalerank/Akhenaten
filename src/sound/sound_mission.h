#pragma once

#include "content/vfs.h"

namespace snd {
    struct mission_config {
        vfs::path briefing;
        vfs::path won;
    };

    void set_mission_config(int mission, pcstr inter, pcstr won);
    mission_config get_mission_config(int mission);
}