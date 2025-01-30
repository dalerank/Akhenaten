#include "building_statue.h"

#include "building/building.h"
#include "building/rotation.h"
#include "city/object_info.h"
#include "city/labor.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "sound/sound_building.h"
#include "core/svector.h"
#include "grid/terrain.h"
#include "grid/building_tiles.h"
#include "io/io_buffer.h"
#include "window/window_building_info.h"
#include "construction/build_planner.h"

template<class T>
struct building_statue_model : public buildings::model_t<T> {
    using inherited = buildings::model_t<T>;
    std::vector<image_desc> var;

    using inherited::load;
    virtual void load(archive arch) override {
        arch.r_array("variants", var, [] (archive arch, auto &item) {
            item.pack = arch.r_int("pack");
            item.id = arch.r_int("id");
            item.offset = arch.r_int("offset");
        });
    }

    virtual void setup_preview_graphics(build_planner &planer) const override {
        int statue_img = building_statue::get_image(T::TYPE, planer.relative_orientation, planer.variant);
        planer.set_tiles_building(statue_img, building_size);
    }
};

building_statue_model<building_small_statue> small_statue_m;
building_statue_model<building_medium_statue> medium_statue_m;
building_statue_model<building_large_statue> large_statue_m;

void building_statue::on_create(int o) {
    int orientation = (4 + building_rotation_global_rotation() + city_view_orientation() / 2) % 4;
    data.monuments.variant = building_rotation_get_building_variant();
    data.monuments.statue_offset = rand() % 4;
}

void building_statue::on_place_update_tiles(int orientation, int variant) {
    int orientation_rel = city_view_relative_orientation(orientation);
    int image_id = get_image(type(), orientation_rel, variant);
    map_building_tiles_add(id(), tile(), size(), image_id, TERRAIN_BUILDING);
}

void building_statue::on_place_checks() {
    /*nothing*/
}

void building_statue::update_map_orientation(int map_orientation) {
    int image_id = get_image_from_value(type(), 0, data.monuments.variant, map_orientation);
    map_building_tiles_add(id(), tile(), base.size, image_id, TERRAIN_BUILDING);
}

void building_statue::bind_dynamic(io_buffer *iob, size_t version) {
    iob->bind____skip(38);
    iob->bind(BIND_SIGNATURE_UINT8, &data.monuments.orientation);
    for (int i = 0; i < 5; i++) {
        iob->bind(BIND_SIGNATURE_UINT16, &data.monuments.workers[i]);
    }
    iob->bind(BIND_SIGNATURE_UINT8, &data.monuments.phase);
    iob->bind(BIND_SIGNATURE_UINT8, &data.monuments.statue_offset);
    iob->bind(BIND_SIGNATURE_UINT8, &data.monuments.temple_complex_attachments);
    iob->bind(BIND_SIGNATURE_UINT8, &data.monuments.variant);

    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &data.monuments.resources_pct[i]);
    }
}

int building_statue_get_variant_size(int type) {
    switch (type) {
    case BUILDING_SMALL_STATUE: return (int)small_statue_m.var.size(); break;
    case BUILDING_MEDIUM_STATUE: return (int)medium_statue_m.var.size(); break;
    case BUILDING_LARGE_STATUE: return (int)large_statue_m.var.size(); break;
    }

    return 0;
}

int building_statue_random_variant(int type, int variant) {
    int size = building_statue_get_variant_size(type);
    return rand() % size;
}

int building_statue_next_variant(int type, int variant) {
    if (variant < 0) {
        return 0;
    }

    int size = building_statue_get_variant_size(type);
    if (!size) {
        return variant;
    }

    variant = (variant + 1) % size;
    return variant;
}

int building_statue::get_image(int type, int orientation, int variant) {
    int image_id = 0;

    int size = building_statue_get_variant_size(type);

    if (!size) {
        return 0;
    }
    //
    while (orientation < 0) { orientation += 4; }
    //
    while (orientation > 3) { orientation -= 4; }

    while (variant < 0) { variant += 4; }

    while (variant > (size - 1)) { variant -= size; }

    switch (type) {
    case BUILDING_SMALL_STATUE:
        variant %= size;
        return image_group(small_statue_m.var[variant]);

    case BUILDING_MEDIUM_STATUE:
        variant %= size;
        return image_group(medium_statue_m.var[variant]);

    case BUILDING_LARGE_STATUE:
        variant %= size;
        return image_group(large_statue_m.var[variant]);
    }

    return image_id;
}

int building_statue::get_image_from_value(int type, int combined, int variant, int map_orientation) {
    int orientation = combined % 4 - (map_orientation / 2);
    return get_image(type, orientation - 1, variant);
}
