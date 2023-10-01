#pragma once

#include "content/vfs.h"

namespace snd {
    void set_building_info_sound(pcstr type, pcstr sound);
    vfs::path get_building_info_sound(pcstr type);
}