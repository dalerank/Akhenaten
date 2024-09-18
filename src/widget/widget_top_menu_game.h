#pragma once

struct mouse;
struct hotkeys;
struct tooltip_context;

void widget_top_menu_clear_state();
void widget_top_menu_draw(int force);
void widget_top_menu_handle_input(const mouse* m, const hotkeys* h);
int widget_top_menu_get_tooltip_text(tooltip_context* c);