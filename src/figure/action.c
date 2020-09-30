#include "action.h"

#include "city/entertainment.h"
#include "city/figures.h"
#include "figure/figure.h"
#include "figuretype/animal.h"
#include "figuretype/cartpusher.h"
#include "figuretype/crime.h"
#include "figuretype/docker.h"
#include "figuretype/editor.h"
#include "figuretype/enemy.h"
#include "figuretype/entertainer.h"
#include "figuretype/maintenance.h"
#include "figuretype/market.h"
#include "figuretype/migrant.h"
#include "figuretype/missile.h"
#include "figuretype/native.h"
#include "figuretype/service.h"
#include "figuretype/soldier.h"
#include "figuretype/trader.h"
#include "figuretype/wall.h"
#include "figuretype/water.h"
#include "core/game_environment.h"

//static void no_action() {
//
//}

void figure::action_perform() {
    if (state) {
        if (targeted_by_figure_id) {
            figure *attacker = figure_get(targeted_by_figure_id);
            if (attacker->state != FIGURE_STATE_ALIVE)
                targeted_by_figure_id = 0;
            if (attacker->target_figure_id != id)
                targeted_by_figure_id = 0;
        }
        switch(type) {
            case 1: immigrant_action(); break;
            case 2: emigrant_action(); break;
            case 3: homeless_action(); break;
            case 4: cartpusher_action(); break;
            case 5: labor_seeker_action(); break;
            case 6: explosion_cloud_action(); break;
            case 7: tax_collector_action(); break;
            case 8: engineer_action(); break;
            case 9: warehouseman_action(); break;
            case 10: prefect_action(); break; //10
            case 11: //soldier_action(); break;
            case 12: //soldier_action(); break;
            case 13: soldier_action(); break;
            case 14: military_standard_action(); break;
            case 15: //entertainer_action(); break;
            case 16: //entertainer_action(); break;
            case 17: //entertainer_action(); break;
            case 18: entertainer_action(); break;
            case 19: trade_caravan_action(); break;
            case 20: trade_ship_action(); break; //20
            case 21: trade_caravan_donkey_action(); break;
            case 22: protestor_action(); break;
            case 23: criminal_action(); break;
            case 24: rioter_action(); break;
            case 25: fishing_boat_action(); break;
            case 26: market_trader_action(); break;
            case 27: priest_action(); break;
            case 28: school_child_action(); break;
            case 29: teacher_action(); break;
            case 30: librarian_action(); break; //30
            case 31: barber_action(); break;
            case 32: bathhouse_worker_action(); break;
            case 33: //doctor_action(); break;
            case 34: doctor_action(); break;
            case 35: worker_action(); break;
            case 36: editor_flag_action(); break;
            case 37: flotsam_action(); break;
            case 38: docker_action(); break;
            case 39: market_buyer_action(); break;
            case 40: patrician_action(); break; //40
            case 41: indigenous_native_action(); break;
            case 42: tower_sentry_action(); break;
            case 43: enemy43_spear_action(); break;
            case 44: enemy44_sword_action(); break;
            case 45: enemy45_sword_action(); break;
            case 46: enemy_camel_action(); break;
            case 47: enemy_elephant_action(); break;
            case 48: enemy_chariot_action(); break;
            case 49: enemy49_fast_sword_action(); break;
            case 50: enemy50_sword_action(); break; //50
            case 51: enemy51_spear_action(); break;
            case 52: enemy52_mounted_archer_action(); break;
            case 53: enemy53_axe_action(); break;
            case 54: enemy_gladiator_action(); break;
//                no_action(); break;
//                no_action(); break;
            case 57: enemy_caesar_legionary_action(); break;
            case 58: native_trader_action(); break;
            case 59: arrow_action(); break;
            case 60: javelin_action(); break; //60
            case 61: bolt_action(); break;
            case 62: ballista_action(); break;
//                no_action(); break;
            case 64: missionary_action(); break;
            case 65: seagulls_action(); break;
            case 66: delivery_boy_action(); break;
            case 67: shipwreck_action(); break;
            case 68: sheep_action(); break;
            case 69: wolf_action(); break;
            case 70: zebra_action(); break; //70
            case 71: spear_action(); break;
            case 72: hippodrome_horse_action(); break;
            default:
                break;
        }
        if (state == FIGURE_STATE_DEAD)
            figure_delete();
    }
}

void figure_action_handle(void) {
    city_figures_reset();
    city_entertainment_set_hippodrome_has_race(0);
    for (int i = 1; i < MAX_FIGURES[GAME_ENV]; i++) {
        figure_get(i)->action_perform();
    }
}
