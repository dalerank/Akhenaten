#include "figuretype/figure_tax_collector.h"

#include "figure/figure.h"
#include "core/profiler.h"
#include "grid/road_access.h"
#include "grid/building.h"
#include "grid/random.h"
#include "city/city_finance.h"
#include "core/calc.h"
#include "city/city_health.h"
#include "city/ratings.h"
#include "city/city.h"
#include "figure/service.h"
#include "building/building_house.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_tax_collector);

void figure_tax_collector::figure_action() {
    OZZY_PROFILER_FUNCTION();
    building* b = home();
    switch (action_state()) {
    case ACTION_40_TAX_COLLECTOR_CREATED:
        base.animctx.frame = 0;
        base.wait_ticks--;
        if (base.wait_ticks <= 0) {
            tile2i road_tile = map_closest_road_within_radius(b->tile, b->size, 2);
            if (road_tile.valid()) {
                base.action_state = ACTION_41_TAX_COLLECTOR_ENTERING_EXITING;
                base.set_cross_country_destination(road_tile);
                base.roam_length = 0;
            } else {
                poof();
            }
        }
        break;

    case ACTION_41_TAX_COLLECTOR_ENTERING_EXITING:
        {
            base.use_cross_country = true;
            const bool finished = base.move_ticks_cross_country(1);
            if (finished) {
                if (base.has_home(map_building_at(tile()))) {
                    // returned to own building
                    poof();
                } else {
                    advance_action(ACTION_42_TAX_COLLECTOR_ROAMING);
                    base.init_roaming_from_building(0);
                    base.roam_length = 0;
                }
            }
        }
        break;

    case ACTION_42_TAX_COLLECTOR_ROAMING:
        base.roam_length++;
        if (base.roam_length >= base.max_roam_length) {
            tile2i road_tile = map_closest_road_within_radius(b->tile, b->size, 2);
            if (road_tile.valid()) {
                advance_action(ACTION_43_TAX_COLLECTOR_RETURNING, road_tile);
            } else {
                poof();
            }
        }

        base.roam_ticks(1);
        if (direction() == DIR_FIGURE_NONE) {
            base.direction = (base.roam_random_counter + map_random_get(tile())) & 6;
        }
        break;

    case ACTION_43_TAX_COLLECTOR_RETURNING:
        base.move_ticks(1);
            if (direction() == DIR_FIGURE_NONE) {
                advance_action(ACTION_41_TAX_COLLECTOR_ENTERING_EXITING);
                base.set_cross_country_destination(b->tile);
                base.roam_length = 0;
            } else if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
                poof();
            }

        break;

    case FIGURE_ACTION_149_CORPSE:
        break;

    default:
        assert(false);
    };
}

sound_key figure_tax_collector::phrase_key() const {
    auto &taxman = runtime_data();

    int all_taxed = taxman.poor_taxed + taxman.middle_taxed + taxman.reach_taxed;
    int poor_taxed = calc_percentage<int>(taxman.poor_taxed, all_taxed);
    
    const int sentiment = g_city.sentiment.value;
    svector<sound_key_state, 16> keys = {
        {"need_more_tax_collectors", g_city.taxes.percentage_taxed_people < 80},
        {"high_taxes", g_city.sentiment.low_mood_cause == LOW_MOOD_HIGH_TAXES},
        {"much_pooh_houses", poor_taxed > 50},
        {"desease_can_start_at_any_moment", g_city.health.value < 30},
        {"no_food_in_city", g_city.sentiment.low_mood_cause == LOW_MOOD_NO_FOOD},
        {"buyer_city_have_no_army", formation_get_num_forts() < 1},
        {"need_workers", g_city.labor.workers_needed >= 10},
        {"gods_are_angry", g_city.religion.least_mood() <= GOD_MOOD_INDIFIRENT},
        {"city_is_bad", g_city.kingdome.rating < 30},
        {"much_unemployments", g_city.sentiment.low_mood_cause == LOW_MOOD_NO_JOBS},
        {"low_entertainment", g_city.festival.months_since_festival > 6},
        {"city_is_good", sentiment > 50},
        {"city_is_amazing", sentiment > 90}
    };

    std::erase_if(keys, [] (auto &it) { return !it.valid; });

    int index = rand() % keys.size();
    return keys[index].prefix;
}

void figure_tax_collector::figure_before_action() {
    building* b = home();
    if (!b->is_valid() || !b->has_figure(0, id())) {
        poof();
    }
}

int figure_tax_collector::provide_service() {
    int max_tax_rate = 0;
    int houses_serviced = figure_provide_service(tile(), &base, [&] (building *b, figure*) {
        auto house = b->dcast_house();
        if (!house) {
            return;
        }

        if (house->house_population() > 0) {
            int tax_multiplier = house->model().tax_multiplier;
            if (tax_multiplier > max_tax_rate) {
                max_tax_rate = tax_multiplier;
            }

            if (house->house_level() < HOUSE_ORDINARY_COTTAGE) {
                runtime_data().poor_taxed++;
            } else if (house->house_level() < HOUSE_COMMON_MANOR) {
                runtime_data().middle_taxed++;
            } else {
                runtime_data().reach_taxed++;
            }

            auto &housed = house->runtime_data();
            housed.tax_collector_id = home()->id;
            housed.tax_coverage = 50;
        }
    });
    base.min_max_seen = max_tax_rate;
    return houses_serviced;
}

figure_sound_t figure_tax_collector::get_sound_reaction(xstring key) const {
    return current_params().sounds[key];
}
