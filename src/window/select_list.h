#pragma once

#include <stdint.h>
#include "core/custom_span.hpp"
#include "core/xstring.h"

void window_select_list_show(int x, int y, int group, int num_items, void (*callback)(int));
void window_select_list_show_text(int x, int y, const custom_span<xstring>& items, void (*callback)(int));
