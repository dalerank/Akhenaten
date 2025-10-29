#include "figuretype/figure_robber.h"

#include "figure/service.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "city/city_message.h"
#include "game/game_events.h"
#include "building/building_house.h"
#include "core/random.h"
#include "grid/road_access.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_robber);

void city_show_message_criminal(xstring message_id, int money_stolen, int tile_offset) {
    bool show_popup_message = false;
    if (g_city.sentiment.last_mugger_message <= 0) {
        g_city.sentiment.last_mugger_message = 90;
        show_popup_message = true;
    }

    events::emit(event_message{ show_popup_message, "message_tutorial_crime", money_stolen, tile_offset });
}


void figure_robber::figure_action() {
    //    terrain_usage = TERRAIN_USAGE_ROADS;
    //    figure_image_increase_offset(32);
    //    cart_image_id = 0;
    //    if (action_state == FIGURE_ACTION_149_CORPSE)
    //        poof();
    switch (action_state()) {
    case ACTION_120_ROBBER_CREATED:
    {
        // if city has palace, all mugger will go there
        base.wait_ticks = 0;
        int senate_id = g_city.buildings.get_palace_id();
        building *b_dst = building_get(senate_id);
        tile2i road_tile = map_closest_road_within_radius(b_dst->tile, b_dst->size, 2);
        if (road_tile.valid()) {
            base.destination_tile = road_tile;
            set_destination(senate_id);
            advance_action(ACTION_121_ROBBER_MOVING);
            route_remove();
        } else {
            advance_action(ACTION_123_ROBBER_LEAVING);
        }
    }
    break;

    case ACTION_123_ROBBER_LEAVING:
    {
        base.wait_ticks = 0;
        tile2i exit = g_city.map.exit_point;
        if (do_goto(exit, TERRAIN_USAGE_ANY)) {
            poof();
        }
    }
    break;

    case ACTION_121_ROBBER_MOVING:
    {
        base.move_ticks(1);
        base.wait_ticks = 0;
        if (direction() == DIR_FIGURE_NONE) {
            poof();
        } else if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
            advance_action(FIGURE_ACTION_120_RIOTER_CREATED);
            route_remove();
        } else if (direction() == DIR_FIGURE_ATTACK) {
            if (base.animctx.frame > 12) {
                base.animctx.frame = 0;
            }
        }
    }
    break;

    case ACTION_122_ROBBER_HIDE:
        poof();
        break;

    }

    base.wait_ticks++;
    if (base.wait_ticks > 200) {
        poof();
        base.animctx.frame = 0;
    }
}

void figure_robber::update_animation() {
    xstring animkey = animkeys().walk;

    if (action_state(FIGURE_ACTION_149_CORPSE)) {
        animkey = animkeys().death; // = image_id_from_group(GROUP_FIGURE_THIEF_DEATH) + figure_image_corpse_offset();
    } else {
        animkey = animkeys().walk; // sprite_image_id = image_id_from_group(GROUP_FIGURE_THIEF_WALK) + CRIMINAL_OFFSETS[anim.frame / 4] + 104;
    }

    image_set_animation(animkey);
}

void figure_robber::create(building *b) {
    g_city.sentiment.criminals++;
    auto house = b->dcast_house();

    if (!house) {
        return;
    }

    auto &housed = house->runtime_data();
    if (housed.criminal_active > 60 && g_city.sentiment.can_create_mugger) {
        housed.criminal_active -= 60;
        tile2i road_tile = map_closest_road_within_radius(b->tile, b->size, 2);
        if (road_tile.valid()) {
            figure *f = figure_create(FIGURE_ROBBER, road_tile, DIR_4_BOTTOM_LEFT);
            f->advance_action(ACTION_120_ROBBER_CREATED);
            f->wait_ticks = 10 + (b->map_random_7bit & 0xf);

            g_city.ratings.monument_record_criminal();
            int taxes_this_year = city_finance_overview_this_year()->income.taxes;
            if (taxes_this_year > 20) {
                int money_stolen = taxes_this_year / 4;
                if (money_stolen > 400) {
                    money_stolen = 400 - random_byte() / 2;
                }

                city_show_message_criminal("message_tutorial_crime", money_stolen, f->tile.grid_offset());
                city_finance_process_stolen(money_stolen);
            } else {
                const int treasury = g_city.finance.treasury;
                int money_stolen = 0;
                if (treasury > 0) {
                    money_stolen = (random_byte() / 2) % 100;
                }

                if (money_stolen > 0) {
                    city_show_message_criminal("message_tutorial_crime", money_stolen, f->tile.grid_offset());
                    city_finance_process_stolen(money_stolen);
                }
            }
        }
    }
}