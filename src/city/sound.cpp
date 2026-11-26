#include "sound.h"

#include "city/city_sound_chunks.h"
#include "core/app_module.h"
#include "core/xvalue.h"
#include "game/simulation.h"
#include "io/chunk_serializer.h"

city_sound_t& city_sound() {
    return xvalue<city_sound_t>::ref();
}

class city_sound_system : public sim_system {
public:
    const char* name() const override { return "city_sound"; }
    void on_reset() override { city_sound().reset(); }
    void push_save_sections() override { g_chunk_io.push_chunk<city_sound_chunk>(city_sound_chunk::size, false); }
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
