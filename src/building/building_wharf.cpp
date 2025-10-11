#include "building_wharf.h"

#include "grid/water.h"
#include "grid/image.h"
#include "grid/building.h"

void building_wharf::on_create(int orientation) {
    base.orientation = orientation;
}

void building_wharf::on_place(int orientation, int variant) {
    int orientation_rel = city_view_relative_orientation(orientation);
    map_water_add_building(id(), tile(), current_params().building_size, base_img() + orientation_rel);

    building_impl::on_place(orientation, variant);
}

void building_wharf::on_place_update_tiles(int orientation, int variant) {
    int orientation_rel = city_view_relative_orientation(orientation);
    map_water_add_building(id(), tile(), size(), base_img() + orientation_rel);
}

void building_wharf::update_map_orientation(int orientation) {
    int image_offset = city_view_relative_orientation(base.orientation);
    int image_id = base_img() + image_offset;
    map_water_add_building(id(), tile(), size(), image_id);
}

void building_wharf::highlight_waypoints() {
    building_impl::highlight_waypoints();

    auto &d = runtime_data();
    map_highlight_set(d.dock_tiles[0], ehighligth_green);
    map_highlight_set(d.dock_tiles[1], ehighligth_green);
}

void building_wharf::bind_dynamic(io_buffer *iob, size_t version) {
    auto &d = runtime_data();
    iob->bind(BIND_SIGNATURE_UINT8, &base.orientation);
    iob->bind(BIND_SIGNATURE_INT32, &d.dock_tiles[0]);
    iob->bind(BIND_SIGNATURE_INT32, &d.dock_tiles[1]);
}

void building_wharf::on_tick(bool refresh_only) {
    auto &anim_wharf = base.anim;
    auto &d = runtime_data();
    if (anim_wharf.valid()) {
        d.docker_anim_frame++;
        d.docker_anim_frame %= (anim_wharf.max_frames * anim_wharf.frame_duration);
    }
}

void building_wharf::update_graphic() {
    building_impl::update_graphic();

    if (!can_play_animation()) {
        set_animation(animkeys().none);
        return;
    }

    int image_warf = map_image_at(tile());
    int image_warf_base = base_img();
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
    auto &d = runtime_data();
    if (anim_wharf.valid()) {
        int img_id = anim_wharf.start_frame() + (d.docker_anim_frame / anim_wharf.frame_duration) * 4;
        const image_t *img = image_get(img_id);
        auto& command = ImageDraw::create_subcommand(render_command_t::ert_generic);
        command.image_id = img_id;
        command.pixel = point + anim_wharf.pos;
        command.mask = color_mask;
        command.flags = ImgFlag_InternalOffset;
    }

    return true;
}

void building_wharf::set_water_access_tiles(const water_access_tiles &tiles) {
    auto &d = runtime_data();
    d.dock_tiles[0] = tiles.point_a.grid_offset();
    d.dock_tiles[1] = tiles.point_b.grid_offset();
}

water_access_tiles building_wharf::get_water_access_tiles() const {
    auto &d = runtime_data();
    return water_access_tiles {
                tile2i{ d.dock_tiles[0] }, tile2i{ d.dock_tiles[1] }
           };
}
