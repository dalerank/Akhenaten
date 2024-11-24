#include "building_wharf.h"

#include "city/labor.h"
#include "grid/water.h"
#include "grid/image.h"

building_transport_wharf::static_params transport_wharf_m;

void building_transport_wharf::static_params::load(archive arch) {

}

void building_wharf::on_create(int orientation) {
    data.dock.orientation = orientation;
}

void building_wharf::on_place_update_tiles(int orientation, int variant) {
    int orientation_rel = city_view_relative_orientation(orientation);
    map_water_add_building(id(), tile(), transport_wharf_m.building_size, anim(animkeys().base).first_img() + orientation_rel);
}

void building_wharf::bind_dynamic(io_buffer *iob, size_t version) {
    iob->bind(BIND_SIGNATURE_UINT8, &data.dock.orientation);
}

inline void building_wharf::on_tick(bool refresh_only) {
    auto &anim_wharf = base.anim;
    if (anim_wharf.valid()) {
        data.dock.docker_anim_frame++;
        data.dock.docker_anim_frame %= (anim_wharf.max_frames * anim_wharf.frame_duration);
    }
}

void building_wharf::update_graphic() {
    building_impl::update_graphic();

    if (!can_play_animation()) {
        set_animation(animkeys().none);
        return;
    }

    int image_warf = map_image_at(tile());
    int image_warf_base = anim(animkeys().base).first_img();
    xstring animkey;
    if (!ship_moored()) {
        if (image_warf == image_warf_base) animkey = animkeys().wait_n;
        else if (image_warf == image_warf_base + 1) animkey = animkeys().wait_w;
        else if (image_warf == image_warf_base + 2) animkey = animkeys().wait_s;
        else animkey = animkeys().wait_e;
    } else {
        if (image_warf == image_warf_base) animkey = animkeys().work_n;
        else if (image_warf == image_warf_base + 1) animkey = animkeys().work_w;
        else if (image_warf == image_warf_base + 2) animkey = animkeys().work_s;
        else animkey = animkeys().work_e;
    }

    set_animation(animkey);
}

bool building_wharf::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    auto &anim_wharf = base.anim;
    if (anim_wharf.valid()) {
        int img_id = anim_wharf.start() + (data.dock.docker_anim_frame / anim_wharf.frame_duration) * 4;
        const image_t *img = image_get(img_id);
        ImageDraw::img_generic(ctx, img_id, point + anim_wharf.pos, color_mask, 1.f, true);
    }

    return true;
}
