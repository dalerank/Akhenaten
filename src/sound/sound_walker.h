#pragma once

#include "content/vfs.h"

namespace snd {
    void set_walker_reaction(pcstr reaction, pcstr sound);
    vfs::path get_walker_reaction(pcstr reaction);
}