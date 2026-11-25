#include "figure/figure.h"
#include "city/city_figures.h"
#include "game/sound_effect.h"
#include "game/game_events.h"

#include "city/city.h"
#include "city/sound.h"
#include "game/sound_effect.h"

void figure::play_die_sound() {

    if (dcast()->play_die_sound()) {
        return;
    }

    int is_soldier = 0;
    int is_citizen = 0;
    int effect = 0;
    switch (type) {
    case FIGURE_BIRDS: effect = SOUND_EFFECT_SHEEP_DIE; break;
    case FIGURE_ANTELOPE: effect = SOUND_EFFECT_ZEBRA_DIE; break;
    case FIGURE_ENEMY_EGYPTIAN_CAMEL: effect = SOUND_EFFECT_CAMEL; break;
    case FIGURE_ENEMY_EGYPTIAN_ELEPHANT: effect = SOUND_EFFECT_ELEPHANT_DIE; break;

    case FIGURE_ENEMY_EGYPTIAN_CHARIOT:
    case FIGURE_ENEMY_EGYPTIAN_MOUNTED_ARCHER:
    case FIGURE_ENEMY_KINGDOME_MOUNTED:
        effect = SOUND_EFFECT_HORSE2;
        break;

    case FIGURE_ARCHER:
    case FIGURE_FCHARIOTEER:
    case FIGURE_INFANTRY:
    case FIGURE_INDIGENOUS_NATIVE:
    case FIGURE_TOWER_SENTRY:
    case FIGURE_ENEMY_EGYPTIAN_SPEAR:
    case FIGURE_ENEMY_EGYPTIAN_HEAVY_SWORD:
   // case FIGURE_ENEMY_EGYPTIAN_FAST_SPEAR:
    case FIGURE_ENEMY_EGYPTIAN_FAST_SWORD:
    case FIGURE_ENEMY_EGYPTIAN_SWORD:
   // case FIGURE_ENEMY_EGYPTIAN_HEAVY_SPEAR:
    case FIGURE_ENEMY_EGYPTIAN_AXE:
    case FIGURE_ENEMY_KINGDOME_JAVELIN:
    case FIGURE_ENEMY_KINGDOME_INFANTRY:
        is_soldier = 1;
        break;

    default:
        is_citizen = 1;
        break;
    }

    if (effect) {
        events::emit(event_sound_effect{effect});
    }

    if (is_soldier) {
        events::emit(event_sound_effect{SOUND_EFFECT_SOLDIER_DIE + city_sound().update_die_soldier()});
    } else if (is_citizen) {
        events::emit(event_sound_effect{SOUND_EFFECT_CITIZEN_DIE + city_sound().update_die_citizen()});
    }

    if (is_enemy()) {
        if (city_figures().total_invading_enemies() == 1) {
            events::emit(event_sound_speech{"Wavs/sword_atk.wav"});
        }
    }
}

void figure::play_sound_file(const xstring& file) {
    events::emit(event_sound_speech{file});
}

void figure::play_hit_sound() {
    int effect = 0;
    switch (type) {
    case FIGURE_INFANTRY:
    case FIGURE_ENEMY_KINGDOME_INFANTRY:
        if (city_sound().update_hit_soldier()) {
            effect = SOUND_EFFECT_SWORD;
        }
        break;

    case FIGURE_FCHARIOTEER:
    case FIGURE_ENEMY_EGYPTIAN_SWORD:
    case FIGURE_ENEMY_EGYPTIAN_CHARIOT:
    case FIGURE_ENEMY_EGYPTIAN_FAST_SWORD:
    case FIGURE_ENEMY_EGYPTIAN_MOUNTED_ARCHER:
    case FIGURE_ENEMY_KINGDOME_MOUNTED:
    case FIGURE_BEDOUIN:
        if (city_sound().update_hit_soldier())
            effect = SOUND_EFFECT_SWORD_SWING;
        break;

    case FIGURE_ARCHER:
        if (city_sound().update_hit_soldier())
            effect = SOUND_EFFECT_LIGHT_SWORD;
        break;

    case FIGURE_ENEMY_EGYPTIAN_SPEAR:
    case FIGURE_ENEMY_KINGDOME_JAVELIN:
    //case FIGURE_ENEMY_EGYPTIAN_HEAVY_SPEAR:
    if (city_sound().update_hit_spear())
        effect = SOUND_EFFECT_SPEAR;
    break;

    //case FIGURE_ENEMY_EGYPTIAN_FAST_SPEAR:
    case FIGURE_ENEMY_EGYPTIAN_HEAVY_SWORD:
        if (city_sound().update_hit_club())
            effect = SOUND_EFFECT_CLUB;

        break;
    case FIGURE_ENEMY_EGYPTIAN_AXE:
        if (city_sound().update_hit_axe())
            effect = SOUND_EFFECT_AXE;

        break;

    case FIGURE_ENEMY_EGYPTIAN_CAMEL:
        effect = SOUND_EFFECT_CAMEL;
        break;

    case FIGURE_ENEMY_EGYPTIAN_ELEPHANT:
        if (city_sound().update_hit_elephant())
            effect = SOUND_EFFECT_ELEPHANT;
        else {
            effect = SOUND_EFFECT_ELEPHANT_HIT;
        }
        break;
        // case FIGURE_DANCER:
        // sound_effect_play(SOUND_EFFECT_LION_ATTACK);
        // break;
        //
        // case FIGURE_WOLF:
        //     if (city_sound().update_hit_wolf())
        //         sound_effect_play(SOUND_EFFECT_WOLF_ATTACK);

        break;
    default:
        break;
    }

    if (effect) {
        events::emit(event_sound_effect{effect});
    }
}
