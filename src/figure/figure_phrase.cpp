#include "figure_phrase.h"

#include "building/building.h"
#include "building/building_bazaar.h"
#include "io/gamefiles/lang.h"
#include "city/city_floods.h"
#include "city/constants.h"
#include "city/city_health.h"
#include "city/ratings.h"
#include "city/city.h"
#include "city/coverage.h"
#include "city/city_labor.h"
#include "city/city_population.h"
#include "city/city_resource.h"
#include "core/calc.h"
#include "core/bstring.h"
#include "empire/trader_handler.h"
#include "figure/formation.h"
#include "figure/figure.h"
#include "sound/sound.h"
#include "sound/sound_walker.h"

#include <string.h>

static int citizen_phrase() {
    //    if (++f->phrase_sequence_exact >= 3)
    //        f->phrase_sequence_exact = 0;
    //
    //    return 7 + f->phrase_sequence_exact;
    return 0;
}

static int tower_sentry_phrase() {
    //    if (++f->phrase_sequence_exact >= 2)
    //        f->phrase_sequence_exact = 0;
    //
    //    int enemies = city_figures_enemies();
    //    if (!enemies)
    //        return 7 + f->phrase_sequence_exact;
    //    else if (enemies <= 10)
    //        return 9;
    //    else if (enemies <= 30)
    //        return 10;
    //    else {
    //        return 11;
    //    }
    return 0;
}

static int soldier_phrase() {
    int enemies = g_city.figures.enemies;
    if (enemies >= 40) {
        return 11;
    } else if (enemies > 20) {
        return 10;
    } else if (enemies) {
        return 9;
    }

    return 0;
}

void figure::figure_phrase_determine() {
    if (id <= 0) {
        return;
    }

    if (!!phrase_key) {
        return;
    }

    if (is_enemy() || type == FIGURE_INDIGENOUS_NATIVE || type == FIGURE_NATIVE_TRADER) {
        phrase_key = "unknown";
        return;
    }
    
    xstring key = dcast()->phrase_key();
    if (!!key) {
        phrase_key = key;
        return;
    } 

    phrase_key = dcast()->default_phrase_key();
}

int figure::figure_play_phrase_file() {
    if (type == 0) {
        return -1;
    }

    xstring path;
    if (phrase_key.empty()) {
        bstring32 prefix = params().name;
        prefix.replace_str("figure_", "");
        path.printf("Voice/Walker/%s_random_%02u.wav", prefix.c_str(), phrase_key.c_str(), rand() % 10);

        if (!g_sound.speech_file_exist(path)) {
            // fallback to standart phrase
            path.printf("Voice/Walker/%s_random_01.wav", prefix.c_str(), phrase_key.c_str());
        }
    } else {
        auto reaction = dcast()->get_sound_reaction(phrase_key);
        path.printf("Voice/Walker/%s", reaction.sound.c_str());
    }

    g_sound.speech_play_file(path, 255);
    return 1;
}