#pragma once

#include "graphics/elements/ui.h"

namespace advisor_population {
void draw_census_graph(ui::widget& w, int full_size, pcstr body, pcstr title);
void draw_society_graph(ui::widget& w, int full_size, pcstr body, pcstr title);
void print_society_info(ui::widget& w);
void print_census_info(ui::widget& w);
void print_history_info(ui::widget& w);
}
