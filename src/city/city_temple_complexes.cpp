#include "city_temple_complexes.h"

#include "building/building_temple_complex.h"
#include "city/buildings.h"
#include "city/city.h"
#include "city/city_kingdome_relations.h"
#include "core/app_module.h"
#include "core/svector.h"
#include "game/simulation.h"

temple_complexes_system city_temple_complexes() {
    return temple_complexes_system({g_city.buildings, g_city.kingdome});
}

class temple_complexes_sim_system : public sim_system {
public:
    const char* name() const override { return "temple_complexes"; }
    void on_year() override { city_temple_complexes().ra_yearly_favour(); }
};

void ANK_REGISTER_APPLICATION_MODULE(register_temple_complexes_system) {
    static temple_complexes_sim_system system;
    g_simulation.register_system(&system);
}

span_const<e_building_type> temple_complexes_system::types() {
    static svector<e_building_type, 16> types;
    types.clear();
    for (int t = BUILDING_NONE + 1; t < BUILDING_MAX && types.size() < types.capacity(); ++t) {
        if (building_static_params::get((e_building_type)t).flags.is_temple_complex) {
            types.push_back((e_building_type)t);
        }
    }
    return make_span(types);
}

building_id temple_complexes_system::id(e_building_type type) const {
    const auto& complexes = _ctx.buildings.tracked_buildings().at(type);
    for (building_id id : complexes) {
        building* b = building_get(id);
        if (b && b->is_valid() && b->type == type) {
            return id;
        }
    }
    return 0;
}

building_id temple_complexes_system::any_id() const {
    for (const e_building_type type : types()) {
        const building_id complex_id = id(type);
        if (complex_id) {
            return complex_id;
        }
    }
    return 0;
}

bool temple_complexes_system::has_any() const {
    return any_id() > 0;
}

bool temple_complexes_system::has_upgrade(e_building_type type, e_temple_compex_upgrade upgrade) const {
    const building_id complex_id = id(type);
    if (!complex_id) {
        return false;
    }
    building* complex_b = building_get(complex_id);
    auto* complex = complex_b ? complex_b->dcast_temple_complex() : nullptr;
    return complex && complex->has_upgrade(upgrade);
}

// OG temple_complex_ra_kingdom_bonus, right after the yearly ratings.
void temple_complexes_system::ra_yearly_favour() {
    if (id(BUILDING_TEMPLE_COMPLEX_RA)) {
        _ctx.kingdome.change(kingdome_state::params().ra_complex_yearly_bonus);
    }
}
