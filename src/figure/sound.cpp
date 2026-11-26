#include "figure/figure_sound.h"

#include "core/xvalue.h"
#include "figure/figure.h"
#include "game/game_events.h"
#include "js/js_register.h"
#include "scenario/scenario.h"

const e_figure_sound_tokens_t ANK_CONFIG_ENUM(e_figure_sound_tokens);
const e_figure_sound_variant_tokens_t ANK_CONFIG_ENUM(e_figure_sound_variant_tokens);

ANK_CONFIG_STRUCT(figure_sound_kinds_t, default_die, hunter_shot, figures)

figure_sound_kinds_t& figure_sound_kinds() {
    return xvalue<figure_sound_kinds_t>::ref();
}

ANK_DECLARE_CONFIG_ITERATOR(config_load_figure_sound_kinds);
void config_load_figure_sound_kinds() {
    call_unload_if_exists(figure_sound_kinds());
    const bool ok = g_config_arch.r("figure_sound_kinds", figure_sound_kinds());
    call_init_if_exists(figure_sound_kinds());
    verify_no_crash_var(ok, "Variable not exist in config: %s", "figure_sound_kinds");
}

void figure_sound_kinds_t::archive_unload() {
    default_die = FIGURE_SOUND_NONE;
    figures.clear();
}

void figure_sound_kinds_t::archive_init() {
    kind_of_type.fill(0);
    for (size_t i = 0; i < figures.size(); ++i) {
        for (e_figure_type type : figures[i].types) {
            if (type > FIGURE_NONE && type < FIGURE_MAX) {
                kind_of_type[type] = (uint8_t)(i + 1);
            }
        }
    }
}

const figure_sound_kind_t& figure_sound_kinds_t::of(e_figure_type type) const {
    static const figure_sound_kind_t none{};
    const int index = (type > FIGURE_NONE && type < FIGURE_MAX) ? kind_of_type[type] : 0;
    return index ? figures[index - 1] : none;
}

void figure::play_die_sound() {
    const auto& kinds = figure_sound_kinds();
    const e_figure_sound die = kinds.of(type).die;
    events::emit(event_sound_figure{id, die ? die : kinds.default_die, FIGURE_SOUND_VARIANT_DIE});
}

void figure::play_hit_sound() {
    const e_figure_sound hit = figure_sound_kinds().of(type).hit;
    events::emit_if(hit != FIGURE_SOUND_NONE, event_sound_figure{id, hit, FIGURE_SOUND_VARIANT_ATTACK});
}

void figure::play_attack_sound() {
    const e_figure_sound attack = figure_sound_kinds().of(type).attack;
    events::emit_if(attack != FIGURE_SOUND_NONE, event_sound_figure{id, attack, FIGURE_SOUND_VARIANT_ATTACK});
}

void figure::play_click_sound() {
    const e_figure_sound click = figure_sound_kinds().of(type).click;
    events::emit_if(click != FIGURE_SOUND_NONE, event_sound_figure{id, click, FIGURE_SOUND_VARIANT_IDLE});
}

void figure::play_hunter_shot_sound() {
    const auto& sounds = figure_sound_kinds().hunter_shot;
    e_figure_sound shot = FIGURE_SOUND_NONE;
    switch (g_scenario.climate) {
    case CLIMATE_CENTRAL:
        shot = sounds.central;
        break;
    case CLIMATE_NORTHERN:
        shot = sounds.northern;
        break;
    case CLIMATE_DESERT:
        shot = sounds.desert;
        break;
    }
    events::emit_if(shot != FIGURE_SOUND_NONE, event_sound_figure{id, shot, FIGURE_SOUND_VARIANT_ATTACK});
}
