#include "window_figure_info.h"

#include "figure/figure.h"
#include "graphics/window.h"
#include "grid/figure.h"
#include "dev/debug.h"
#include "window/building/figures.h"
#include "js/js_game.h"
#include "js/js_struct.h"
#include "graphics/elements/ui_js.h"
#include "window/figure_info_thumbnails.h"

struct figure_info_window_init { int figure_id; };
ANK_REGISTER_STRUCT_WRITER(figure_info_window_init, figure_id);

figure_info_window::figure_info_window() {
    window_figure_register_handler(this);
}

void figure_info_window::window_info_foreground(object_info &c) {
    common_info_window::window_info_foreground(c);

    figure *f = c.figure_get();
    g_debug_figure_id = c.figure_get_id();

    bool custom_window = f->dcast()->window_info_background(c);
    if (custom_window) {
        return;
    }

    c.figure_drawn = 1;
}

void figure_info_window::archive_load(archive arch) {
    common_info_window::archive_load(arch);
    assert(elements.size() > 0);
    arch.r("related_figures", related_figures);
}

void figure_info_window::init(object_info &c) {
    g_figure_info_thumbnails.clear();
    for (size_t i = 0; i < c.figure_ids.size(); ++i) {
        g_figure_info_thumbnails.prepare_thumbnail((int)i, c.figure_ids[i]);
    }
    g_figure_info_thumbnails.finish();

    ui.check_errors = false;
    const int figure_id = c.figure_ids[c.figure_selected_index];
    bvariant_map::scoped js_j;
    js_helper::writer(*js_j, figure_info_window_init{ figure_id });
    ui::dispatch_autoconfig_es_event(this, __func__, *js_j);
}

bool figure_info_window::check(object_info &c) {
    return figure_type_any_of(c.figure_get(), related_figures);
}

figure *figure_info_window::figure_get(object_info &c) {
    int figure_id = c.grid_offset ? map_figure_id_get(c.grid_offset) : 0;
    return ::figure_get(figure_id);
}
