#include "building_temple_complex.h"

#include "city/city.h"
#include "game/undo.h"
#include "grid/building_tiles.h"
#include "grid/terrain.h"
#include "grid/image.h"
#include "construction/build_planner.h"

template<class T>
struct building_temple_complex_model : public buildings::model_t<T> {
    using inherited = buildings::model_t<T>;

    using inherited::load;
    virtual void load(archive arch) override {
    }

    virtual void planer_setup_preview_graphics(build_planner &planer) const override {
        inherited::planer_setup_preview_graphics(planer);
    }
};

building_temple_complex_model<building_temple_complex_osiris> building_temple_complex_osiris_m;
building_temple_complex_model<building_temple_complex_ra> building_temple_complex_ra_m;
building_temple_complex_model<building_temple_complex_ptah> building_temple_complex_ptah_m;
building_temple_complex_model<building_temple_complex_seth> building_temple_complex_seth_m;
building_temple_complex_model<building_temple_complex_bast> building_temple_complex_bast_m;

void building_temple_complex::on_create(int orientation) {
    data.monuments.variant = (10 - (2 * orientation)) % 8; // ugh!
}

void building_temple_complex::on_post_load() {
    const bool is_active = num_workers() > 0;
    g_city.buildings.track_building(base, is_active);
}

building *add_temple_complex_element(int x, int y, int orientation, building *prev) {
    building *b = building_create(prev->type, tile2i(x, y), orientation);
    game_undo_add_building(b);

    b->size = 3;
    b->prev_part_building_id = prev->id;
    prev->next_part_building_id = b->id;
    int image_id = map_image_at(tile2i(x, y));
    map_building_tiles_add(b->id, b->tile, 3, image_id, TERRAIN_BUILDING);

    return b;
}

void building_temple_complex::on_place(int orientation, int variant) {
    g_city_planner.add_building_tiles_from_list(id(), false);

    tile2i offset = { 0, 0 };
    switch (orientation) {
    case 0: offset = { 0, -3 }; break;
    case 1: offset = { 3, 0 }; break;
    case 2: offset = { 0, 3 }; break;
    case 3: offset = { -3, 0 }; break;
    }

    building *altar = add_temple_complex_element(tilex() + offset.x(), tiley() + offset.y(), orientation, &base);
    building *oracle = add_temple_complex_element(tilex() + 2 * offset.x(), tiley() + 2 * offset.y(), orientation, altar);
}

void building_temple_complex::update_count() const {
    const bool is_active = num_workers() > 0;
    g_city.buildings.track_building(base, is_active);
}
