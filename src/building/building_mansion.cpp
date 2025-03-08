#include "building_mansion.h"

#include "window/building/common.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/text.h"
#include "graphics/elements/button.h"
#include "graphics/elements/generic_button.h"
#include "city/city.h"
#include "city/victory.h"
#include "city/buildings.h"
#include "city/finance.h"
#include "city/ratings.h"
#include "widget/city/ornaments.h"
#include "graphics/image.h"
#include "graphics/animation.h"
#include "grid/road_access.h"
#include "figure/figure.h"

buildings::model_t<building_personal_mansion> personal_mansion_m;
buildings::model_t<building_family_mansion> family_mansion_m;
buildings::model_t<building_dynasty_mansion> dynasty_mansion_m;

void building_mansion::on_place(int orientation, int variant) {
    building_impl::on_place(orientation, variant);

    city_buildings_add_mansion(&base);
}

void building_mansion::spawn_figure() {
    common_spawn_figure_trigger(50);

    if (base.has_figure(BUILDING_SLOT_GOVERNOR)) {
        return;
    }

    tile2i road_tile = map_closest_road_within_radius(tile(), size(), 2);
    if (road_tile.valid()) {
        figure *f = figure_create(FIGURE_GOVERNOR, road_tile, DIR_4_BOTTOM_LEFT);
        f->advance_action(FIGURE_ACTION_120_GOVERNOR_CREATED);
        f->set_home(&base);
        f->wait_ticks = 10 + (base.map_random_7bit & 0xf);
        base.set_figure(BUILDING_SLOT_GOVERNOR, f);
    }
}

void building_mansion::update_graphic() {
    set_animation(animkeys().work);
}

int building_mansion::window_info_handle_mouse(const mouse *m, object_info &c) {
    return 0;
}

bool building_mansion::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) {
    int max_workers = model()->laborers;
    switch (type()) {
    case BUILDING_PERSONAL_MANSION: 
    case BUILDING_FAMILY_MANSION:
    case BUILDING_DYNASTY_MANSION:
        {
            const animation_t &ranim = anim(animkeys().work);
            draw_normal_anim(ctx, point, tile, mask);
        }
        break;

    default:
        assert(false);
    }
    return true;
}
