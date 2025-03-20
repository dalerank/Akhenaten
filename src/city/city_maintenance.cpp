#include "city_maintenance.h"

#include "building/building.h"
#include "grid/random.h"
#include "grid/routing/routing_terrain.h"
#include "city/sentiment.h"
#include "city/city_buildings.h"
#include "core/profiler.h"
#include "core/random.h"
#include "scenario/scenario.h"
#include "city/city.h"
#include "city/city_warnings.h"
#include "city/message.h"
#include "game/undo.h"

void city_maintenance_t::collapse_building(building *b) {
    city_message_apply_sound_interval(MESSAGE_CAT_COLLAPSE);

    g_city_events.enqueue(event_collase_damage{ b->id });
    city_message_post_with_popup_delay(MESSAGE_CAT_COLLAPSE, false, MESSAGE_COLLAPSED_BUILDING, b->type, b->tile.grid_offset());

    game_undo_disable();
    b->destroy_by_collapse();
}

void city_maintenance_t::init() {
}

void city_maintenance_t::check_fire_collapse() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Fire Collapse Update");
    city_sentiment_reset_protesters_criminals();

    int climate = scenario_property_climate();
    int recalculate_terrain = 0;
    random_generate_next();
    int random_global = random_byte() & 7;

    buildings_valid_do([&] (building &b) {
        const model_building *model = model_get_building(b.type);

        /////// COLLAPSE
        int damage_risk_increase = model->damage_risk;
        damage_risk_increase += scenario_additional_damage(b.type, /*collapse*/1);

        if (!b.damage_proof) {
            b.damage_risk += damage_risk_increase;
        }

        if (b.damage_risk > 1000) {
            collapse_building(&b);
            recalculate_terrain = 1;
            return;
        }

        /////// FIRE
        int random_building = (b.id + map_random_get(b.tile)) & 7;
        if (!b.fire_proof && random_building == random_global) {
            int expected_fire_risk = building_impl::params(b.type).fire_risk_update;
            expected_fire_risk += model->fire_risk;

            expected_fire_risk += scenario_additional_damage(b.type, /*fire*/0);
            expected_fire_risk = b.dcast()->get_fire_risk(expected_fire_risk);
            b.fire_risk += expected_fire_risk;
            //            if (climate == CLIMATE_NORTHERN)
            //                b->fire_risk = 0;
            //            else if (climate == CLIMATE_DESERT)
            //                b->fire_risk += 30;
        }

        if (b.fire_risk > 1000) {
            b.destroy_by_fire();
            recalculate_terrain = 1;
        }
    });

    if (recalculate_terrain) {
        map_routing_update_land();
    }
}