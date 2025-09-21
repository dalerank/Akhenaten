#pragma once

#include "core/buffer.h"

void scenario_revolt_init();

void scenario_revolt_process();

int scenario_revolt_is_in_progress();

int scenario_revolt_is_finished();

void scenario_revolt_save_state(buffer* buf);

void scenario_revolt_load_state(buffer* buf);