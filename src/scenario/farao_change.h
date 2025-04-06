#pragma once

#include "core/buffer.h"

void scenario_kingdome_change_init(void);

void scenario_kingdome_change_process(void);

void scenario_kingdome_change_save_state(buffer* time, buffer* state);

void scenario_kingdome_change_load_state(buffer* time, buffer* state);
