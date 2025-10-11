#include "window/window_building_info.h"

#include "building/building_garden.h"
#include "sound/sound_building.h"
#include "grid/terrain.h"

struct info_window_garden : public building_info_window_t<info_window_garden> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override;
};

info_window_garden garden_infow;

void info_window_garden::init(object_info &c) {
    common_info_window::init(c);

    window_building_play_sound(&c, snd::get_building_info_sound(BUILDING_GARDENS));

    const auto &params = building_static_params::get(BUILDING_GARDENS);
    ui["title"] = ui::str(params.meta.text_id, 0);
    ui["text"] = ui::str(params.meta.text_id, 1);
}

bool info_window_garden::check(object_info &c) {
    return !!map_terrain_is(c.grid_offset, TERRAIN_GARDEN);
}