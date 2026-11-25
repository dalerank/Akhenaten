#include "sound.h"

#include "city/city_sound_chunks.h"
#include "core/app_module.h"
#include "core/xvalue.h"
#include "game/simulation.h"
#include "io/chunk_serializer.h"
#include "io/gamestate/save_versions.h"

city_sound_t& city_sound() {
    return xvalue<city_sound_t>::ref();
}

class city_sound_system : public sim_system {
public:
    const char* name() const override { return "city_sound"; }
    void on_reset() override { city_sound().reset(); }
    void push_save_sections(int file_version) override {
        if (file_version >= save_version_city_sections) {
            g_chunk_io.push_chunk<city_sound_chunk>(city_sound_chunk::size, false);
        }
    }
};

void ANK_REGISTER_APPLICATION_MODULE(register_city_sound_system) {
    static city_sound_system system;
    g_simulation.register_system(&system);
}

void city_sound_t::reset() {
    *this = {};
}

static int update_field(int8_t* field, int max_value) {
    (*field)--;
    if (*field <= 0) {
        *field = (int8_t)max_value;
        return 1;
    } else {
        return 0;
    }
}

int city_sound_t::update_march_enemy() {
    return update_field(&march_enemy, 200);
}

int city_sound_t::update_march_horse() {
    return update_field(&march_horse, 200);
}

int city_sound_t::update_shoot_arrow() {
    return update_field(&shoot_arrow, 10);
}

int city_sound_t::update_hit_soldier() {
    return update_field(&hit_soldier, 8);
}

int city_sound_t::update_hit_axe() {
    return update_field(&hit_axe, 8);
}

int city_sound_t::update_hit_club() {
    return update_field(&hit_club, 8);
}

int city_sound_t::update_hit_spear() {
    return update_field(&hit_spear, 8);
}

int city_sound_t::update_hit_elephant() {
    if (hit_elephant == 1)
        hit_elephant = 0;
    else
        hit_elephant = 1;

    return hit_elephant;
}

int city_sound_t::update_die_citizen() {
    die_citizen++;
    if (die_citizen >= 4)
        die_citizen = 0;

    return die_citizen;
}

int city_sound_t::update_die_soldier() {
    die_soldier++;
    if (die_soldier >= 4)
        die_soldier = 0;

    return die_soldier;
}
