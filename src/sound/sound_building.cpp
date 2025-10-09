#include "sound_building.h"

#include <unordered_set>
#include <string>

#include "js/js_game.h"

struct building_sound_t {
    e_building_type type;
    xstring sound;

    bool operator==(const building_sound_t &other) const noexcept { return type == other.type; }
    bool operator!=(const building_sound_t &other) const noexcept { return type != other.type; }
    bool operator<(const building_sound_t &other) const noexcept { return type < other.type; }
};

template<>
struct std::hash<building_sound_t> {
    std::size_t operator()(const building_sound_t &k) const noexcept {
        return k.type;
    }
};
ANK_CONFIG_STRUCT(building_sound_t, type, sound)

std::unordered_set<building_sound_t> ANK_VARIABLE(building_sounds);

xstring snd::get_building_info_sound(e_building_type type) {
    auto it = building_sounds.find({ type });

    static xstring empty_sound = "Wavs/empty.wav";
    return (it == building_sounds.end()) ? empty_sound : it->sound;
}