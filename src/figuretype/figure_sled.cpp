#include "figure_sled.h"

#include "core/profiler.h"
#include "building/monuments.h"
#include "graphics/graphics.h"

#include "js/js_game.h"

struct sled_model : public figures::model_t<FIGURE_SLED, figure_sled> {};
sled_model sled_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_figure_sled);
void config_load_figure_sled() {
    g_config_arch.r_section("figure_sled", [] (archive arch) {
        sled_m.anim.load(arch);
        sled_m.sounds.load(arch);
    });
}

void figure_sled::figure_action() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/Sled");
    if (base.leading_figure_id > 0) {
        figure* leader = figure_get(base.leading_figure_id);
        if (leader->type == FIGURE_SLED_PULLER && leader->state == FIGURE_STATE_ALIVE) {
            follow_ticks(1);
        } else {
            grid_area area = building_monument_get_area(destination());
            if (map_tile_is_inside_area(tile(), area.tmin, area.tmax)) {
                do_deliver(ACTION_11_RETURNING_EMPTY);
            }
            poof();
            return;
        }
    }

    switch (base.resource_id) {
    case RESOURCE_STONE: image_set_animation(IMG_BIGSLED_STONE, 0, 1); break;
    case RESOURCE_LIMESTONE: image_set_animation(IMG_BIGSLED_LIMESTONE, 0, 1); break;
    case RESOURCE_GRANITE: image_set_animation(IMG_BIGSLED_GRANITE, 0, 1); break;
    case RESOURCE_SANDSTONE: image_set_animation(IMG_BIGSLED_SANDSTONE, 0, 1); break;
    case RESOURCE_CLAY: image_set_animation(IMG_BIGSLED_CLAY, 0, 1); break;
    case RESOURCE_BRICKS: image_set_animation(IMG_BIGSLED_BRICKS, 0, 1); break;

    default:
        image_set_animation(IMG_BIGSLED_EMPTY, 0, 1);
        break;
    }
}

void figure_sled::do_deliver(int action_done) {
    base.anim.frame = 0;
    wait_ticks++;

    int carrying = base.get_carrying_amount();
    e_resource resource = base.get_resource();

    if (resource == RESOURCE_NONE || carrying <= 0) {
        base.progress_inside_speed = 0;
        return advance_action(action_done);
    }

    building* dest = destination();
    switch (dest->type) {
    case BUILDING_SMALL_MASTABA:
        building_monument_deliver_resource(dest, resource, carrying);
        break;
    };
}