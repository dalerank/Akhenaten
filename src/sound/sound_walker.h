#pragma once

#include "content/vfs.h"

namespace snd {
    void set_walker_reaction(pcstr reaction, pcstr sound);
    bstring64 get_walker_reaction(pcstr reaction);
}