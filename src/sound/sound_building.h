#pragma once

#include "content/vfs.h"
#include "building/building_type.h"

namespace snd {
    vfs::path get_building_info_sound(e_building_type type);
}