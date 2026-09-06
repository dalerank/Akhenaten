#include "figure_snapshot.h"

#include "city/city_figures.h"
#include "figure/figure.h"
#include "game/game.h"
#include "graphics/graphics.h"
#include "graphics/view/view.h"
#include "widget/widget_city.h"

#include <utility>

void figure_snapshot::swap(figure_snapshot& other) noexcept {
    std::swap(texture_id_, other.texture_id_);
    std::swap(size_, other.size_);
}

void figure_snapshot::reset() {
    if (texture_id_) {
        graphics_delete_saved_texture(texture_id_);
        texture_id_ = 0;
    }
    size_ = 0;
}

bool figure_snapshot::capture(int figure_id, int size, vec2i crop_offset) {
    figure* f = figure_get(figure_id);
    if (size <= 0 || !f || !f->is_alive()) {
        return false;
    }

    // The renderer only reuses a saved texture when the size matches; a resized snapshot has to
    // drop the old one itself or it stays allocated with nobody holding its id.
    if (size_ != size) {
        reset();
    }

    const vec2i saved_camera = g_camera.camera_position;
    g_camera.go_to_mappoint(f->tile);

    painter ctx = game.painter();
    g_screen_city.draw_for_figure(ctx, figure_id);

    const vec2i coord = f->main_cached_pos;
    // Outside the viewport after the snap (map edge / stale sort skip): keep what we had.
    if (coord.x <= 0 && coord.y <= 0) {
        g_camera.go_to_pixel(saved_camera, false);
        return false;
    }

    const int captured = graphics_save_to_texture(texture_id_, coord + crop_offset, {size, size});
    g_camera.go_to_pixel(saved_camera, false);

    if (!captured) {
        return false;
    }

    texture_id_ = captured;
    size_ = size;
    return true;
}
