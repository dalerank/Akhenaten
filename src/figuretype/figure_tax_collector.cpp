#include "figuretype/figure_tax_collector.h"

#include "figure/figure.h"
#include "core/profiler.h"
#include "grid/road_access.h"
#include "grid/building.h"
#include "city/finance.h"
#include "city/sentiment.h"
#include "core/calc.h"
#include "city/health.h"
#include "city/labor.h"
#include "city/gods.h"
#include "city/ratings.h"
#include "city/city.h"
#include "figure/service.h"

#include "js/js_game.h"

struct tax_collector_model : figures::model_t<FIGURE_TAX_COLLECTOR, figure_tax_collector> {};
tax_collector_model tax_collector_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_figure_tax_collector);
void config_load_figure_tax_collector() {
    g_config_arch.r_section("figure_tax_collector", [] (archive arch) {
        tax_collector_m.anim.load(arch);
        tax_collector_m.sounds.load(arch);
    });
}

void figure_tax_collector::figure_action() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/Tax Collector");
    building* b = home();
    switch (action_state()) {
    case FIGURE_ACTION_40_TAX_COLLECTOR_CREATED:
        base.anim_frame = 0;
        wait_ticks--;
        if (wait_ticks <= 0) {
            tile2i road_tile;
            if (map_closest_road_within_radius(b->tile, b->size, 2, road_tile)) {
                base.action_state = FIGURE_ACTION_41_TAX_COLLECTOR_ENTERING_EXITING;
                base.set_cross_country_destination(road_tile.x(), road_tile.y());
                base.roam_length = 0;
            } else {
                poof();
            }
        }
        break;

    case FIGURE_ACTION_41_TAX_COLLECTOR_ENTERING_EXITING:
        base.use_cross_country = true;
        if (base.move_ticks_cross_country(1) == 1) {
            if (base.has_home(map_building_at(tile()))) {
                // returned to own building
                poof();
            } else {
                base.action_state = FIGURE_ACTION_42_TAX_COLLECTOR_ROAMING;
                base.init_roaming_from_building(0);
                base.roam_length = 0;
            }
        }
        break;

    case ACTION_10_DELIVERING_FOOD:
    case FIGURE_ACTION_42_TAX_COLLECTOR_ROAMING:
        base.roam_length++;
        if (base.roam_length >= base.max_roam_length) {
            tile2i road_tile;
            if (map_closest_road_within_radius(b->tile, b->size, 2, road_tile)) {
                base.action_state = FIGURE_ACTION_43_TAX_COLLECTOR_RETURNING;
                destination_tile = road_tile;
            } else {
                poof();
            }
        }
        base.roam_ticks(1);
        break;

    case ACTION_11_RETURNING_EMPTY:
    case FIGURE_ACTION_43_TAX_COLLECTOR_RETURNING:
        base.move_ticks(1);
            if (direction() == DIR_FIGURE_NONE) {
                base.action_state = FIGURE_ACTION_41_TAX_COLLECTOR_ENTERING_EXITING;
                base.set_cross_country_destination(b->tile.x(), b->tile.y());
                base.roam_length = 0;
            } else if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
                poof();
            }

        break;
    };
}

sound_key figure_tax_collector::phrase_key() const {
    auto &taxman = base.local_data.taxman;

    int all_taxed = taxman.poor_taxed + taxman.middle_taxed + taxman.reach_taxed;
    int poor_taxed = calc_percentage<int>(taxman.poor_taxed, all_taxed);
    
    svector<sound_key_state, 16> keys = {
        {"need_more_tax_collectors", city_finance_percentage_taxed_people() < 80},
        {"high_taxes", city_sentiment_low_mood_cause() == LOW_MOOD_HIGH_TAXES},
        {"much_pooh_houses", poor_taxed > 50},
        {"desease_can_start_at_any_moment", g_city.health.value < 30},
        {"no_food_in_city", city_sentiment_low_mood_cause() == LOW_MOOD_NO_FOOD},
        {"buyer_city_have_no_army", formation_get_num_forts() < 1},
        {"need_workers", g_city.labor.workers_needed >= 10},
        {"gods_are_angry", city_gods_least_mood() <= GOD_MOOD_INDIFIRENT},
        {"city_is_bad", g_city.ratings.kingdom < 30},
        {"much_unemployments", city_sentiment_low_mood_cause() == LOW_MOOD_NO_JOBS},
        {"low_entertainment", g_city.festival.months_since_festival > 6},
        {"city_is_good", city_sentiment() > 50},
        {"city_is_amazing", city_sentiment() > 90}
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


static void tax_collector_coverage(building* b, figure *f, int &max_tax_multiplier) {
    if (b->house_size && b->house_population > 0) {
        int tax_multiplier = model_get_house(b->subtype.house_level)->tax_multiplier;
        if (tax_multiplier > max_tax_multiplier) {
            max_tax_multiplier = tax_multiplier;
        }

        if (b->subtype.house_level < HOUSE_ORDINARY_COTTAGE) {
            f->local_data.taxman.poor_taxed++;
        } else if (b->subtype.house_level < HOUSE_COMMON_MANOR) {
            f->local_data.taxman.middle_taxed++;
        } else {
            f->local_data.taxman.reach_taxed++;
        }
        b->tax_collector_id = f->home()->id;
        b->house_tax_coverage = 50;
    }
}

int figure_tax_collector::provide_service() {
    int max_tax_rate = 0;
    int houses_serviced = figure_provide_service(tile(), &base, max_tax_rate, tax_collector_coverage);
    base.min_max_seen = max_tax_rate;
    return houses_serviced;
}

figure_sound_t figure_tax_collector::get_sound_reaction(pcstr key) const {
    return tax_collector_m.sounds[key];
}
