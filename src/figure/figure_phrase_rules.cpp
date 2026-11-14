#include "figure/figure_phrase.h"

#include "building/building.h"
#include "building/building_dock.h"
#include "building/building_temple_complex.h"
#include "city/city.h"
#include "city/city_figures.h"
#include "city/city_floods.h"
#include "city/city_problems.h"
#include "city/constants.h"
#include "core/bstring.h"
#include "core/calc.h"
#include "figure/figure.h"
#include "figure/figure_static_params.h"
#include "figuretype/figure_bricklayer.h"
#include "figuretype/figure_caravan_donkey.h"
#include "figuretype/figure_carpenter.h"
#include "figuretype/figure_cartpusher.h"
#include "figuretype/figure_constable.h"
#include "figuretype/figure_docker.h"
#include "figuretype/figure_fireman.h"
#include "figuretype/figure_fishing_boat.h"
#include "figuretype/figure_hunter.h"
#include "figuretype/figure_kingdome_trader.h"
#include "figuretype/figure_lumberjack.h"
#include "figuretype/figure_market_buyer.h"
#include "figuretype/figure_reed_gatherer.h"
#include "figuretype/figure_stonemason.h"
#include "figuretype/figure_storageyard_cart.h"
#include "figuretype/figure_tomb_artisan.h"
#include "figuretype/figure_trader_ship.h"
#include "figuretype/figure_transport_ship.h"
#include "figuretype/figure_war_ship.h"
#include "figuretype/figure_worker.h"
#include "game/game_config.h"
#include "io/gamefiles/lang.h"
#include "scenario/scenario.h"

struct figure_speech_sound_t {
    int32_t type;
    int32_t speech;
};
ANK_CONFIG_STRUCT(figure_speech_sound_t, type, speech)

struct figure_speech_phrases_t {
    int32_t speech;
    svector<xstring, 20> files;
};
ANK_CONFIG_STRUCT(figure_speech_phrases_t, speech, files)

svector<figure_speech_sound_t, 64> ANK_VARIABLE(figure_speech_sounds);
svector<figure_speech_phrases_t, 64> ANK_VARIABLE(figure_speech_phrases);

namespace {

    enum {
        SPEECH_BY_FESTIVAL_WALKER = -4,
        SPEECH_BY_TEMPLE_GOD = -3,
        SPEECH_NONE = -1,
        SPEECH_PRIEST_OSIRIS = 230,
        PHRASE_FAR_DISTANCE = 25,
    };

    // The first figure type of the remake's own walkers; OG types all come before it.
    constexpr e_figure_type FIGURE_REMAKE_TYPES_BEGIN = FIGURE_PHARAOH;

    int speech_of_type(e_figure_type type) {
        for (const auto& s : figure_speech_sounds) {
            if (s.type == type) {
                return s.speech;
            }
        }
        return SPEECH_NONE;
    }

    // OG building_temple_god.
    int temple_god(const building* b) {
        if (!b) {
            return -1;
        }
        switch (b->type) {
        case BUILDING_TEMPLE_OSIRIS:
        case BUILDING_TEMPLE_COMPLEX_OSIRIS:
            return GOD_OSIRIS;
        case BUILDING_TEMPLE_RA:
        case BUILDING_TEMPLE_COMPLEX_RA:
            return GOD_RA;
        case BUILDING_TEMPLE_PTAH:
        case BUILDING_TEMPLE_COMPLEX_PTAH:
            return GOD_PTAH;
        case BUILDING_TEMPLE_SETH:
        case BUILDING_TEMPLE_COMPLEX_SETH:
            return GOD_SETH;
        case BUILDING_TEMPLE_BAST:
        case BUILDING_TEMPLE_COMPLEX_BAST:
            return GOD_BAST;
        default:
            return -1;
        }
    }

    const building* home_of(const figure& f) {
        return f.home_building_id ? building_get(f.home_building_id) : nullptr;
    }

    // OG keeps the walker a festival guy stands for in resource_id; the remake knows it by the home building.
    e_figure_type festival_walker(const figure& f) {
        const building* home = home_of(f);
        if (!home) {
            return FIGURE_NONE;
        }
        if (temple_god(home) >= 0) {
            return FIGURE_PRIEST;
        }
        switch (home->type) {
        case BUILDING_JUGGLER_SCHOOL:
            return FIGURE_JUGGLER;
        case BUILDING_CONSERVATORY:
            return FIGURE_MUSICIAN;
        case BUILDING_DANCE_SCHOOL:
            return FIGURE_DANCER;
        default:
            return FIGURE_NONE;
        }
    }

    e_figure_type speech_type(const figure& f) {
        return (f.type == FIGURE_FESTIVAL_GUY) ? festival_walker(f) : f.type;
    }

    const svector<xstring, 20>* speech_files(int speech) {
        for (const auto& p : figure_speech_phrases) {
            if (p.speech == speech) {
                return &p.files;
            }
        }
        return nullptr;
    }

    // The script sound entry of an OG speech file: its key and text.
    const figure_sounds_map::value_type* sound_entry_for_file(e_figure_type type, const xstring& file) {
        if (type == FIGURE_NONE || file.empty()) {
            return nullptr;
        }
        for (const auto& item : figure_static_params::get(type).sounds.data) {
            if (!item.second.sound.empty() && bstring64(item.second.sound.c_str()).icmp(file.c_str()) == 0) {
                return &item;
            }
        }
        return nullptr;
    }

    const std::array<e_advisor, CITY_PROBLEM_COUNT> problem_advisors = {
      ADVISOR_HEALTH,       // CITY_PROBLEM_HEALTH
      ADVISOR_CHIEF,        // CITY_PROBLEM_FOOD
      ADVISOR_MILITARY,     // CITY_PROBLEM_INVASION
      ADVISOR_LABOR,        // CITY_PROBLEM_WORKER_SHORTAGE
      ADVISOR_RELIGION,     // CITY_PROBLEM_GODS
      ADVISOR_RATINGS,      // CITY_PROBLEM_KINGDOM
      ADVISOR_LABOR,        // CITY_PROBLEM_UNEMPLOYMENT
      ADVISOR_ENTERTAINMENT // CITY_PROBLEM_ENTERTAINMENT
    };

    struct phrase_state {
        figure& f;
        int phrase = FIGURE_PHRASE_NONE;
        e_advisor group = ADVISOR_NONE;

        int next_sequence(int limit, int restart) {
            uint8_t seq = (uint8_t)(f.phrase_sequence + 1);
            f.phrase_sequence = (seq >= limit) ? (uint8_t)restart : seq;
            return f.phrase_sequence;
        }
        void say(int p) { phrase = p; }
        void say(e_advisor g, int p) {
            group = g;
            phrase = p;
        }
    };

    bool far_from_source(const figure& f) {
        return calc_maximum_distance(f.destination_tile, f.source_tile) >= PHRASE_FAR_DISTANCE;
    }

    bool traded_nothing(empire_trader_handle trader) {
        return !trader.has_traded();
    }

    figure* caravan_head(figure& f) {
        if (f.type == FIGURE_TRADE_CARAVAN_DONKEY) {
            auto* donkey = f.dcast()->dcast_caravan_donkey();
            return donkey ? donkey->head_of_caravan() : nullptr;
        }
        return &f;
    }

    enum e_dock_activity { DOCK_NONE, DOCK_BUYING, DOCK_SELLING };

    // OG figure_trade_ship_dock_activity.
    e_dock_activity trade_ship_dock_activity(const figure& f) {
        building* b = f.destination_building_id ? building_get(f.destination_building_id) : nullptr;
        if (!b || b->state != BUILDING_STATE_VALID) {
            return DOCK_BUYING;
        }
        building_dock* dock = b->dcast_dock();
        if (!dock) {
            return DOCK_BUYING;
        }
        for (short docker_id : dock->runtime_data().docker_ids) {
            if (docker_id == 0) {
                continue;
            }
            const figure* docker = figure_get(docker_id);
            if (!docker || docker->state != FIGURE_STATE_ALIVE) {
                continue;
            }
            switch (docker->action_state) {
            case ACTION_1_DOCKER_IMPORT_QUEUE:
            case ACTION_3_DOCKER_IMPORT_GOING_TO_WAREHOUSE:
            case ACTION_7_DOCKER_IMPORT_AT_WAREHOUSE:
            case ACTION_6_DOCKER_IMPORT_RETURNING:
                return DOCK_BUYING;
            case ACTION_2_DOCKER_EXPORT_QUEUE:
            case ACTION_4_DOCKER_EXPORT_GOING_TO_WAREHOUSE:
            case ACTION_5_DOCKER_EXPORT_RETURNING:
            case ACTION_9_DOCKER_EXPORT_AT_WAREHOUSE:
                return DOCK_SELLING;
            }
        }
        return DOCK_NONE;
    }

    int enemy_warships() {
        int count = 0;
        figure_valid_do([&](figure& f) {
            if (f.dcast()->dcast_enemy_warship()) {
                count++;
            }
        });
        return count;
    }

    bool is_crime_figure(figure_id id) {
        const figure* f = id > 0 ? figure_get(id) : nullptr;
        return f && (f->type == FIGURE_ROBBER || f->type == FIGURE_PROTESTER);
    }

    // OG figure_phrase_determine: the figure's own phrase, or FIGURE_PHRASE_NONE.
    void determine_own_phrase(phrase_state& st) {
        figure& f = st.f;
        const int action = f.action_state;
        const bool event_running = g_scenario.events.any_invasion_running();

        switch (f.type) {
        case FIGURE_IMMIGRANT:
            st.say(st.next_sequence(3, 0));
            break;

        case FIGURE_EMIGRANT:
            switch (g_city.sentiment.low_mood_cause) {
            case LOW_MOOD_NO_FOOD:
                st.say(ADVISOR_LABOR, 1);
                break;
            case LOW_MOOD_NO_JOBS:
                st.say(ADVISOR_LABOR, 0);
                break;
            case LOW_MOOD_HIGH_TAXES:
                st.say(ADVISOR_FINANCIAL, 2);
                break;
            default:
                st.say(ADVISOR_LABOR, 3);
                break;
            }
            break;

        case FIGURE_HOMELESS:
            st.say(ADVISOR_CHIEF, st.next_sequence(2, 0));
            break;

        case FIGURE_CART_PUSHER:
            if (action == ACTION_20_CARTPUSHER_INITIAL) {
                if (f.min_max_seen == 2) {
                    st.say(ADVISOR_LABOR, 0);
                } else if (f.min_max_seen == 1) {
                    st.say(1);
                }
            } else if (action == ACTION_9_CARTPUSHER_DELIVERING_TO_WAREHOUSE
                       || action == ACTION_10_CARTPUSHER_DELIVERING_TO_GRANARY
                       || action == ACTION_11_CARTPUSHER_DELIVERING_TO_WORKSHOP
                       || action == ACTION_21_CARTPUSHER_DELIVERING_TO_WAREHOUSE_LEGACY
                       || action == ACTION_22_CARTPUSHER_DELIVERING_TO_GRANARY_LEGACY
                       || action == ACTION_23_CARTPUSHER_DELIVERING_TO_WORKSHOP_LEGACY) {
                if (far_from_source(f)) {
                    st.say(2);
                }
            }
            break;

        case FIGURE_LABOR_SEEKER:
            if (g_city.labor.unemployment_percentage > 5) {
                st.say(10);
            } else if (g_city.labor.workers_needed > 5) {
                st.say(11);
            }
            break;

        case FIGURE_TAX_COLLECTOR: {
            const auto& fin = g_city.taxes;
            const int taxed = fin.taxed_nobles + fin.taxed_citizens;
            const int total = fin.untaxed_nobles + fin.untaxed_citizens + taxed;
            st.group = ADVISOR_FINANCIAL;
            if (total > 0 && (taxed * 100) / total < 50) {
                st.phrase = 10;
            } else if (f.min_max_seen >= 7) {
                st.phrase = 11;
            } else if (f.min_max_seen >= 1) {
                st.phrase = 12;
            }
            break;
        }

        case FIGURE_ARCHITECT:
            // OG adds (min_max_seen >= 600), which a byte never reaches.
            st.say(10);
            break;

        case FIGURE_STORAGEYARD_CART:
            if (action == ACTION_50_WAREHOUSECART_CREATED) {
                if (f.min_max_seen == 2) {
                    st.say(1);
                }
            } else if (action == ACTION_51_WAREHOUSECART_DELIVERING_RESOURCE
                       || action == ACTION_9_WAREHOUSECART_DELIVERING_GOODS) {
                if (far_from_source(f)) {
                    st.say(2);
                }
            }
            break;

        case FIGURE_FIREMAN:
            st.next_sequence(13, 0);
            if (action == ACTION_5_FIREMAN_AT_FIRE) {
                st.phrase = f.phrase_sequence;
            }
            break;

        case FIGURE_JUGGLER:
        case FIGURE_MUSICIAN:
        case FIGURE_DANCER:
        case FIGURE_SENET_PLAYER:
        case FIGURE_TEACHER:
        case FIGURE_LIBRARIAN:
        case FIGURE_DENTIST:
        case FIGURE_NOBLES:
        case FIGURE_WATER_CARRIER:
        case FIGURE_ZOOKEEPER:
            break;

        case FIGURE_TRADE_CARAVAN:
        case FIGURE_TRADE_CARAVAN_DONKEY: {
            uint8_t seq = (uint8_t)(f.phrase_sequence + 1);
            f.phrase_sequence = (seq > 2) ? 1 : seq;
            st.group = ADVISOR_TRADE;
            st.phrase = f.phrase_sequence + 1;
            figure* head = caravan_head(f);
            auto* caravan = head ? head->dcast()->dcast_trade_caravan() : nullptr;
            if (!caravan) {
                break;
            }
            if (action == ACTION_3_TRADE_CARAVAN_LEAVING) {
                if (traded_nothing(caravan->empire_trader())) {
                    st.phrase = 0;
                }
            } else if (action == ACTION_2_TRADE_CARAVAN_TRADING) {
                building* dest = caravan->destination();
                if (caravan->can_buy(dest, caravan->empire_city())) {
                    st.phrase = 4;
                } else if (caravan->can_sell(dest, caravan->empire_city())) {
                    st.phrase = 3;
                }
            }
            break;
        }

        case FIGURE_TRADE_SHIP: {
            st.group = ADVISOR_TRADE;
            auto* ship = f.dcast()->dcast_trade_ship();
            if (action == ACTION_115_TRADE_SHIP_LEAVING) {
                st.phrase = (ship && traded_nothing(ship->empire_trader())) ? 2 : 4;
            } else if (action == ACTION_112_TRADE_SHIP_MOORED) {
                switch (trade_ship_dock_activity(f)) {
                case DOCK_BUYING:
                    st.phrase = 1;
                    break;
                case DOCK_SELLING:
                    st.phrase = 0;
                    break;
                default:
                    st.phrase = 2;
                    break;
                }
            } else {
                st.phrase = 3;
            }
            break;
        }

        case FIGURE_ROBBER:
            st.say(ADVISOR_CHIEF, st.next_sequence(4, 0));
            break;

        case FIGURE_TOMB_ROBER:
            st.say(ADVISOR_MONUMENTS, st.next_sequence(2, 0));
            break;

        case FIGURE_FISHING_BOAT:
            switch (action) {
            case ACTION_0_FISHING_BOAT_CREATED:
            case ACTION_4_FISHING_BOAT_AT_WHARF:
                st.say(2);
                break;
            case ACTION_1_FISHING_BOAT_GOING_TO_FISH:
            case ACTION_2_FISHING_BOAT_FISHING:
                st.say(0);
                break;
            case ACTION_3_FISHING_BOAT_GOING_TO_WHARF:
            case ACTION_5_FISHING_BOAT_RETURNING_WITH_FISH:
                st.say(1);
                break;
            }
            break;

        case FIGURE_MARKET_TRADER:
            st.say(ADVISOR_TRADE, action != ACTION_126_ROAMER_RETURNING ? 1 : 0);
            break;

        case FIGURE_PRIEST: {
            const building* home = home_of(f);
            switch (temple_god(home)) {
            case GOD_OSIRIS:
                if (g_floods.quality_current < 60 && g_floods.has_floodplains) {
                    st.say(ADVISOR_CHIEF, 11);
                }
                break;
            case GOD_RA:
                if (g_city.kingdome.rating < 20) {
                    st.say(ADVISOR_RATINGS, 11);
                }
                break;
            case GOD_PTAH:
                if (g_city.labor.workers_needed > 10) {
                    st.say(ADVISOR_LABOR, 11);
                }
                break;
            case GOD_SETH:
                if (event_running) {
                    st.say(ADVISOR_MILITARY, 11);
                }
                break;
            case GOD_BAST: {
                const building_temple_complex* complex
                  = home ? const_cast<building*>(home)->dcast_temple_complex() : nullptr;
                if (complex && complex->has_upgrade(etc_upgrade_oracle)) {
                    st.say(ADVISOR_HEALTH, 13);
                } else if (g_city.sentiment.value < 60) {
                    st.say(ADVISOR_CHIEF, 11);
                } else if (g_city.avg_coverage.average_entertainment < 60) {
                    st.say(ADVISOR_ENTERTAINMENT, 12);
                }
                break;
            }
            }
            break;
        }

        case FIGURE_PHYSICIAN:
            if (g_city.health.value < 40) {
                st.say(ADVISOR_HEALTH, 10);
            }
            break;

        case FIGURE_HERBALIST:
            // OG adds (min_max_seen > 800), which a byte never reaches.
            st.say(ADVISOR_HEALTH, 1);
            break;

        case FIGURE_EMBALMER:
            if (g_city.health.value < 30) {
                st.say(ADVISOR_HEALTH, 10);
            }
            break;

        case FIGURE_DOCKER:
            if (action == ACTION_3_DOCKER_IMPORT_GOING_TO_WAREHOUSE
                || action == ACTION_4_DOCKER_EXPORT_GOING_TO_WAREHOUSE) {
                if (far_from_source(f)) {
                    st.phrase = 2;
                }
                st.group = ADVISOR_TRADE;
            }
            break;

        case FIGURE_MARKET_BUYER:
            if (action == ACTION_145_MARKET_BUYER_GOING_TO_STORAGE) {
                st.say(ADVISOR_TRADE, 10);
            } else if (action == ACTION_146_MARKET_BUYER_RETURNING) {
                st.say(ADVISOR_TRADE, 11);
            }
            break;

        case FIGURE_TOWER_SENTRY: {
            const int enemies = g_city.figures.enemies;
            if (enemies == 0) {
                st.say(ADVISOR_MILITARY, 0);
            } else if (event_running) {
                st.say(ADVISOR_MILITARY, 1);
            } else if (enemies <= 10) {
                st.say(ADVISOR_MILITARY, 2);
            } else if (enemies <= 30) {
                st.say(ADVISOR_MILITARY, 3);
            }
            break;
        }

        case FIGURE_DELIVERY_BOY:
            st.say(ADVISOR_TRADE, st.next_sequence(3, 0));
            break;

        case FIGURE_OSTRICH_HUNTER:
        case FIGURE_ANTELOPE_HUNTER:
        case FIGURE_BIRDS_HUNTER:
            st.say(action == ACTION_12_OSTRICH_HUNTER_MOVE_PACKED ? 1 : 0);
            break;

        case FIGURE_LUMBERJACK:
            st.say(ADVISOR_TRADE, action == ACTION_4_LUMBERJACK_RETURN_HOME ? 1 : 0);
            break;

        case FIGURE_REED_GATHERER:
            st.say(ADVISOR_TRADE, action == ACTION_11_REED_GATHERER_RETURN_HOME ? 1 : 0);
            break;

        case FIGURE_TRANSPORT_SHIP: {
            const int enemies = g_city.figures.enemies;
            st.group = ADVISOR_FLEET;
            if (enemies != 0 && action == ACTION_215_TRANSPORT_SHIP_EVADING) {
                st.phrase = 0;
            } else if (enemy_warships() != 0) {
                st.phrase = 1;
            } else {
                st.phrase = event_running ? 2 : 3;
            }
            break;
        }

        case FIGURE_WARSHIP: {
            const int enemies = g_city.figures.enemies;
            const bool hunting = action == ACTION_10_WARSHIP_HUNTING;
            const bool evading = action == ACTION_12_WARSHIP_EVADING;
            st.group = ADVISOR_FLEET;
            if (enemies != 0 && hunting) {
                st.phrase = 0;
            } else if (enemies != 0 && evading) {
                st.phrase = 1;
            } else if (!hunting && !evading && enemy_warships() != 0) {
                st.phrase = 2;
            } else {
                st.phrase = event_running ? 3 : 4;
            }
            break;
        }

        case FIGURE_CARPENTER:
            st.say(ADVISOR_MONUMENTS, action != ACTION_1_CARPENTER_GO_TO_SITE ? 1 : 0);
            break;

        case FIGURE_STONEMASON:
            st.say(ADVISOR_MONUMENTS, action != ACTION_1_MASON_GOING ? 1 : 0);
            break;

        case FIGURE_TOMB_ARTISAN:
            st.say(ADVISOR_MONUMENTS, action != ACTION_11_TOMB_ARTISAN_GOING ? 1 : 0);
            break;

        case FIGURE_BRICKLAYER:
            st.say(ADVISOR_MONUMENTS, action != ACTION_1_BRICKLAYER_GO_TO_SITE ? 1 : 0);
            break;

        case FIGURE_LABORER: {
            bool working = false;
            switch (action) {
            case ACTION_15_LABORER_TO_STORAGE_YARD:
            case ACTION_16_LABORER_AT_STORAGE_YARD:
            case ACTION_17_LABORER_TO_PYRAMID:
            case ACTION_18_LABORER_CLIMB_RAMP:
            case ACTION_19_LABORER_TO_MASON:
            case ACTION_20_LABORER_WALK_TO_MASON:
            case ACTION_21_LABORER_TO_LEVEL_TILE:
            case ACTION_22_LABORER_LEVEL_WORK:
            case ACTION_23_LABORER_SLED_TO_SUN_TEMPLE:
            case ACTION_26_LABORER_SLED_TO_MAUSOLEUM:
            case ACTION_30_LABORER_SLED_AT_RAMP:
                working = true;
                break;
            }
            if (figure_worker::farm_work_waiting()) {
                st.say(11);
            } else if (working) {
                st.say(ADVISOR_MONUMENTS, 12);
            }
            break;
        }

        case FIGURE_CONSTABLE:
            st.next_sequence(4, 0);
            if (action == ACTION_150_CONSTABLE_ATTACK) {
                if (is_crime_figure(f.target_figure_id) || is_crime_figure(f.targeted_by_figure_id)) {
                    st.say(ADVISOR_CHIEF, 13);
                } else {
                    st.say(f.phrase_sequence + 14);
                }
            } else if (f.min_max_seen < 100) {
                // OG says city-life 12 from 500 on, which a byte never reaches.
                st.say(10);
            } else {
                st.say(ADVISOR_CHIEF, 11);
            }
            break;

        case FIGURE_MAGISTRATE:
            // OG says 11 while city_player.monument_completion_flag is set, which nothing sets, and city-life 14 from
            // 500 on, which a byte never reaches.
            if (f.min_max_seen >= 100) {
                st.say(ADVISOR_CHIEF, 13);
            } else {
                st.say(12);
            }
            break;

        case FIGURE_FESTIVAL_GUY:
            st.say(ADVISOR_RELIGION, 10);
            break;

        case FIGURE_SLED_PULLER:
            st.say(ADVISOR_MONUMENTS, 12);
            break;

        case FIGURE_PLAGUED_CITIZEN:
            st.say(ADVISOR_HEALTH, 0);
            break;

        default:
            break;
        }
    }

} // namespace

bool figure_phrase_is_og(e_figure_type type) {
    if (game_features::gameplay_change_walker_phrases_remake.to_bool()) {
        return false;
    }
    return type < FIGURE_REMAKE_TYPES_BEGIN || speech_of_type(type) != SPEECH_NONE;
}

// OG building_info.c figure_speaks.
bool figure_phrase_speaks(e_figure_type type) {
    switch (type) {
    case FIGURE_LABOR_SEEKER:
    case FIGURE_TAX_COLLECTOR:
    case FIGURE_FIREMAN:
    case FIGURE_JUGGLER:
    case FIGURE_MUSICIAN:
    case FIGURE_DANCER:
    case FIGURE_SENET_PLAYER:
    case FIGURE_PRIEST:
    case FIGURE_TEACHER:
    case FIGURE_LIBRARIAN:
    case FIGURE_DENTIST:
    case FIGURE_PHYSICIAN:
    case FIGURE_EMBALMER:
    case FIGURE_WORKER:
    case FIGURE_MARKET_BUYER:
    case FIGURE_NOBLES:
    case FIGURE_WATER_CARRIER:
    case FIGURE_CONSTABLE:
    case FIGURE_MAGISTRATE:
    case FIGURE_ZOOKEEPER:
        return true;
    default:
        return false;
    }
}

void figure_phrase_determine(figure& f) {
    phrase_state st{f};
    determine_own_phrase(st);
    // OG falls through to the city's problems only for the talkers that have no phrase of their own (the worker
    // never gets here: OG's switch has no case for it).
    if (st.phrase == FIGURE_PHRASE_NONE && f.type != FIGURE_WORKER && figure_phrase_speaks(f.type)) {
        const int problem = city_problem_pick_current();
        st.phrase = problem;
        st.group = (problem >= CITY_PROBLEM_COUNT) ? ADVISOR_CHIEF : problem_advisors[problem];
    }
    f.phrase_id = (int8_t)st.phrase;
    f.phrase_group = st.group;
}

// OG figure_phrase_sound_id: the speech id is also the text group of the phrases.
int figure_phrase_speech_id(const figure& f) {
    const e_figure_type type = speech_type(f);
    const int speech = speech_of_type(type);
    if (speech == SPEECH_BY_TEMPLE_GOD) {
        const int god = temple_god(home_of(f));
        return god >= 0 ? SPEECH_PRIEST_OSIRIS + god : SPEECH_NONE;
    }
    return speech > 0 ? speech : SPEECH_NONE;
}

xstring figure_phrase_sound_file(const figure& f) {
    const int speech = figure_phrase_speech_id(f);
    const auto* files = speech_files(speech);
    if (!files || f.phrase_id < 0 || f.phrase_id >= (int)files->size()) {
        return {};
    }
    return files->at(f.phrase_id);
}

xstring figure_phrase_text(const figure& f) {
    if (f.phrase_id < 0) {
        return {};
    }
    const xstring file = figure_phrase_sound_file(f);
    if (const auto* item = sound_entry_for_file(speech_type(f), file)) {
        const figure_sound_t& entry = item->second;
        if (!entry.text.empty()) {
            return entry.text;
        }
        if (entry.group > 0) {
            return xstring(lang_get_string(entry.group, entry.id));
        }
    }
    const int speech = figure_phrase_speech_id(f);
    pcstr text = speech > 0 ? lang_get_string(speech, f.phrase_id) : nullptr;
    return (text && *text) ? xstring(text) : xstring{};
}

void figure_phrase_apply(figure& f) {
    const xstring file = figure_phrase_sound_file(f);
    const auto* item = sound_entry_for_file(speech_type(f), file);
    f.phrase_key = item ? item->first : file;
    f.phrase_sound = file;
}

bool figure_phrase_has_other_problem(const figure& f) {
    return figure_phrase_speaks(f.type) && city_problem_other_loaded(f.phrase_id);
}

void figure_phrase_next_problem(figure& f) {
    const int next = city_problem_next(f.phrase_id);
    if (next == f.phrase_id) {
        return;
    }
    f.phrase_id = (int8_t)next;
    f.phrase_group = problem_advisors[next];
    figure_phrase_apply(f);
}

int figure_phrase_advisor(const figure& f) {
    return f.phrase_group;
}
