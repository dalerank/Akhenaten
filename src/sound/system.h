#pragma once

#include "content/vfs.h"

void sound_system_init();
void sound_system_shutdown();
void sound_system_update_channel(int channel, vfs::path filename);
