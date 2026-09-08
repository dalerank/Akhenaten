#include "figure_info_thumbnails.h"

#include "dev/debug.h"
#include "game/game.h"
#include "js/js_game.h"
#include "widget/widget_city.h"

declare_console_var_int(figure_small_image_x, -32)
declare_console_var_int(figure_small_image_y, -48)

figure_info_thumbnails g_figure_info_thumbnails;

void figure_info_thumbnails::clear() {
    figure_images_.clear();
}

void figure_info_thumbnails::prepare_thumbnail(int index, figure_id id) {
    if (index < 0 || index >= MAX_THUMBNAILS) {
        return;
    }

    assert((int)figure_images_.size() == index);
    figure_images_.emplace_back();
    figure_images_[index].capture(id, THUMBNAIL_SIZE, {figure_small_image_x(), figure_small_image_y()},
      e_figure_snapshot_mode::figure_only);
}

void figure_info_thumbnails::finish() {
    painter ctx = game.painter();
    g_screen_city.draw(ctx);
}

int figure_info_thumbnails::texture(int index) const {
    if (index < 0 || index >= (int)figure_images_.size()) {
        return 0;
    }
    return figure_images_[index].texture_id();
}

int __figure_info_tab_texture(int index) {
    return g_figure_info_thumbnails.texture(index);
}
ANK_FUNCTION_1(__figure_info_tab_texture)
