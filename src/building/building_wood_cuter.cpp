#include "building_wood_cuter.h"

#include "figure/figure.h"
#include "building/count.h"
#include "core/random.h"
#include "js/js_game.h"
#include "building_raw_material.h"
#include "widget/city/ornaments.h"
#include "city/labor.h"

buildings::model_t<building_wood_cutter> bwood_cutter_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_bwood_cutter);
void config_load_building_bwood_cutter() {
    bwood_cutter_m.load();
}

void building_wood_cutter::on_create(int orientation) {
    base.output_resource_first_id = RESOURCE_TIMBER;
    data.industry.max_gatheres = 1;
}

void building_wood_cutter::update_count() const {
    building_increase_industry_count(RESOURCE_TIMBER, num_workers() > 0);
}

void building_wood_cutter::spawn_figure() {
    check_labor_problem();
    if (has_road_access()) {
        common_spawn_labor_seeker(100);
        int pct_workers = worker_percentage();
        int spawn_delay = figure_spawn_timer();
        if (spawn_delay == -1) {
            return;
        }

        base.figure_spawn_delay++;
        if (base.figure_spawn_delay > spawn_delay) {
            base.figure_spawn_delay = 0;

            if (base.can_spawn_gatherer(FIGURE_LUMBERJACK, data.industry.max_gatheres, 50)) {
                auto f = create_figure_generic(FIGURE_LUMBERJACK, ACTION_8_RECALCULATE, BUILDING_SLOT_SERVICE, DIR_4_BOTTOM_LEFT);
                random_generate_next();
                f->wait_ticks = random_short() % 30; // ok
            }
        }
    }
    base.common_spawn_goods_output_cartpusher();
}

void building_wood_cutter::window_info_background(object_info &ctx) {
    building_raw_material_draw_info(ctx, "timber_yard", RESOURCE_TIMBER);
}

bool building_wood_cutter::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    const auto &anim = bwood_cutter_m.anim["work"];
    building_draw_normal_anim(ctx, point, &base, tile, anim, color_mask);

    return true;
}