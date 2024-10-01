#pragma once

#include "core/buffer.h"
#include "core/vec2i.h"

#include <functional>

void scenario_invasion_clear(void);

void scenario_invasion_init(void);

bool scenario_invasion_exists_upcoming(void);

void scenario_invasion_foreach_warning(std::function<void(vec2i, int)> callback);

int scenario_invasion_count(void);

int scenario_invasion_start_from_mars(void);

int scenario_invasion_start_from_caesar(int size);

void scenario_invasion_start_from_cheat(void);

void scenario_invasion_start_from_console(int attack_type, int size, int invasion_point);

void scenario_invasion_process(void);
