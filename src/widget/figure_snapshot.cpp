#include "figure_snapshot.h"
#include "grid/figure.h"

#include "city/city_figures.h"
#include "figure/figure.h"
#include "game/game.h"
#include "graphics/graphics.h"
#include "graphics/view/view.h"
#include "graphics/view/zoom.h"
#include "widget/widget_city.h"

#include <algorithm>
#include <utility>

namespace {

    // The snapshot is a fixed-size window on the city, so it is always taken at 100%: the draw
    // path renders unscaled here, while the camera centres the figure in tiles, and size_tiles
    // is zoom-dependent. Left at the player's zoom the figure lands off the captured frame.
    class scoped_unzoom {
    public:
        explicit scoped_unzoom(viewport_t& view) {
            if (g_zoom.get_percentage() != 100.f) {
                g_zoom.set_value(100.f);
                view.refresh_viewport();
            }
        }

        ~scoped_unzoom() {
            g_zoom.zoom = saved_zoom_;
            g_zoom.target = saved_target_;
        }

        scoped_unzoom(const scoped_unzoom &) = delete;
        scoped_unzoom &operator=(const scoped_unzoom &) = delete;

    private:
        const float saved_zoom_ = g_zoom.zoom;
        const float saved_target_ = g_zoom.target;
    };

    // Keeps the whole crop inside the city viewport. Near a map edge the camera cannot centre
    // the figure, and an unclamped rect would read outside the render target: the renderer hands
    // it straight to SDL, which clips the source and stretches whatever is left.
    vec2i clamp_crop_to_viewport(const viewport_t& view, vec2i crop, int size) {
        const vec2i view_min = view.offset;
        const vec2i view_max = view.offset + view.size_pixels;

        crop.x = std::clamp(crop.x, view_min.x, std::max(view_min.x, view_max.x - size));
        crop.y = std::clamp(crop.y, view_min.y, std::max(view_min.y, view_max.y - size));
        return crop;
    }

} // namespace

void figure_snapshot::swap(figure_snapshot &other) noexcept {
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

bool figure_snapshot::capture(int figure_id, int size, vec2i crop_offset, e_figure_snapshot_mode mode) {
    figure *f = figure_get(figure_id);
    if (size <= 0 || !f || !f->is_alive()) {
        return false;
    }

    // The renderer only reuses a saved texture when the size matches; a resized snapshot has to
    // drop the old one itself or it stays allocated with nobody holding its id.
    if (size_ != size) {
        reset();
    }

    viewport_t view = g_camera;
    bool captured_ok = false;
    {
        const scoped_unzoom unzoom(view);
        view.go_to_mappoint(f->tile);

        painter ctx = game.painter();
        ctx.view = &view;
        g_screen_city.draw_for_figure(ctx, mode == e_figure_snapshot_mode::figure_only ? figure_id : 0);

        // Outside the viewport after the snap (map edge / stale sort skip): keep what we had.
        const vec2i coord = map_figure_draw_state(f->id).main_pos;
        if (coord.x > 0 || coord.y > 0) {
            const vec2i crop = clamp_crop_to_viewport(view, coord + crop_offset, size);
            if (const int captured = graphics_save_to_texture(texture_id_, crop, {size, size})) {
                texture_id_ = captured;
                size_ = size;
                captured_ok = true;
            }
        }
    }

    return captured_ok;
}
