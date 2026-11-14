#include "figure_priest.h"

#include "building/building_house.h"
#include "building/building_temple_complex.h"
#include "figure/service.h"
#include "figuretype/figure_plagued_citizen.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_priest);

void figure_priest::static_params::archive_load(archive arch) {
    gods.clear();
    for (const xstring& config : god_configs) {
        god_params& p = gods.emplace_back();
        (figure_static_params&)p = (const figure_static_params&)*this;
        p.config = config;
        p.name = p.config.c_str();
        const bool loaded = g_config_arch.r(p.config.c_str(), p);
        verify_no_crash_var(loaded, "Variable not exist in config: %s", p.config.c_str());
        p.initialize();
    }
}

const figure_priest::god_params* figure_priest::god() const {
    const building* temple = home();
    for (const god_params& p : current_params().gods) {
        if (std::find(p.temples.begin(), p.temples.end(), temple->type) != p.temples.end()) {
            return &p;
        }
    }
    return nullptr;
}

const figure_impl::static_params& figure_priest::params() const {
    const god_params* p = god();
    if (p) {
        return *p;
    }
    return current_params();
}

void figure_priest::figure_before_action() {
    building* b = home();
    if (!b->is_valid() || !b->has_figure(0, id())) {
        poof();
    }
}

static uint8_t& temple_coverage(building_house& house, e_god god) {
    auto& d = house.runtime_data();
    switch (god) {
    case GOD_RA:
        return d.temple_ra;
    case GOD_PTAH:
        return d.temple_ptah;
    case GOD_SETH:
        return d.temple_seth;
    case GOD_BAST:
        return d.temple_bast;
    default:
        return d.temple_osiris;
    }
}

int figure_priest::provide_service() {
    const god_params* p = god();
    if (!p) {
        return 0;
    }

    building* main = home()->main();
    auto* complex = main ? main->dcast_temple_complex() : nullptr;
    const bool cures_plague = p->altar_cures_plague && complex && complex->has_upgrade(etc_upgrade_altar);
    const e_god god = p->god;
    const int houses_serviced = figure_provide_service(tile(), &base, [god, cures_plague](building* b, figure* f) {
        auto house = b->dcast_house();
        if (!house) {
            return;
        }
        if (house->house_population() > 0) {
            temple_coverage(*house, god) = MAX_COVERAGE;
        }
        if (cures_plague) {
            building* main = &house->main()->base;
            if (main->has_plague) {
                main->has_plague = false;
                main->disease_days = 0;
            }
        }
    });
    if (cures_plague) {
        figure_plagued_citizen::cure_nearby(tile(), 1);
    }

    return houses_serviced;
}
