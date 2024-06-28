#include "figure/figure.h"

#include "city/city.h"
#include "city/sound.h"
#include "sound/effect.h"
#include "sound/sound.h"

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
    case FIGURE_ENEMY46_CAMEL: effect = SOUND_EFFECT_CAMEL; break;
    case FIGURE_ENEMY47_ELEPHANT: effect = SOUND_EFFECT_ELEPHANT_DIE; break;

    case FIGURE_ENEMY48_CHARIOT:
    case FIGURE_ENEMY52_MOUNTED_ARCHER:
        effect = SOUND_EFFECT_HORSE2;
        break;

    case FIGURE_ARCHER:
    case FIGURE_FCHARIOTEER:
    case FIGURE_INFANTRY:
    case FIGURE_INDIGENOUS_NATIVE:
    case FIGURE_TOWER_SENTRY:
    case FIGURE_ENEMY43_SPEAR:
    case FIGURE_ENEMY44_SWORD:
    case FIGURE_ENEMY45_SWORD:
    case FIGURE_ENEMY49_FAST_SWORD:
    case FIGURE_ENEMY50_SWORD:
    case FIGURE_ENEMY51_SPEAR:
    case FIGURE_ENEMY53_AXE:
    case FIGURE_ENEMY54_GLADIATOR:
    case FIGURE_ENEMY_CAESAR_JAVELIN:
    case FIGURE_ENEMY_CAESAR_MOUNTED:
    case FIGURE_ENEMY_CAESAR_LEGIONARY:
        is_soldier = 1;
        break;

    default:
        is_citizen = 1;
        break;
    }

    if (effect) {
        g_sound.play_effect(effect);
    }

    if (is_soldier) {
        g_sound.play_effect(SOUND_EFFECT_SOLDIER_DIE + city_sound_update_die_soldier());
    } else if (is_citizen) {
        g_sound.play_effect(SOUND_EFFECT_CITIZEN_DIE + city_sound_update_die_citizen());
    }

    if (is_enemy()) {
        if (g_city.figures.enemies == 1) {
            g_sound.speech_play_file("Wavs/army_war_cry.wav", 255);
        }
    }
}

void figure::play_hit_sound() {
    int effect = 0;
    switch (type) {
    case FIGURE_INFANTRY:
    case FIGURE_ENEMY_CAESAR_LEGIONARY:
        if (city_sound_update_hit_soldier()) {
            effect = SOUND_EFFECT_SWORD;
        }
        break;

    case FIGURE_FCHARIOTEER:
    case FIGURE_ENEMY45_SWORD:
    case FIGURE_ENEMY48_CHARIOT:
    case FIGURE_ENEMY50_SWORD:
    case FIGURE_ENEMY52_MOUNTED_ARCHER:
    case FIGURE_ENEMY54_GLADIATOR:
        if (city_sound_update_hit_soldier())
            effect = SOUND_EFFECT_SWORD_SWING;
        break;

    case FIGURE_ARCHER:
        if (city_sound_update_hit_soldier())
            effect = SOUND_EFFECT_LIGHT_SWORD;
        break;

    case FIGURE_ENEMY43_SPEAR:
    case FIGURE_ENEMY51_SPEAR:
        if (city_sound_update_hit_spear())
            effect = SOUND_EFFECT_SPEAR;
        break;

    case FIGURE_ENEMY44_SWORD:
    case FIGURE_ENEMY49_FAST_SWORD:
        if (city_sound_update_hit_club())
            effect = SOUND_EFFECT_CLUB;

        break;
    case FIGURE_ENEMY53_AXE:
        if (city_sound_update_hit_axe())
            effect = SOUND_EFFECT_AXE;

        break;

    case FIGURE_ENEMY46_CAMEL:
        effect = SOUND_EFFECT_CAMEL;
        break;

    case FIGURE_ENEMY47_ELEPHANT:
        if (city_sound_update_hit_elephant())
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
        //     if (city_sound_update_hit_wolf())
        //         sound_effect_play(SOUND_EFFECT_WOLF_ATTACK);

        break;
    default:
        break;
    }

    if (effect) {
        g_sound.play_effect(effect);
    }
}
