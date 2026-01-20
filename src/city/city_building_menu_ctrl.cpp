#include "city_building_menu_ctrl.h"

#include "city/buildings.h"
#include "city/city.h"
#include "empire/empire.h"
#include "game/tutorial.h"
#include "game/game_config.h"
#include "scenario/scenario.h"

#include "core/archive.h"
#include "core/log.h"
#include "io/gamefiles/lang.h"
#include "city/city_industry.h"
#include "game/game_events.h"
#include "building/building_temple_complex.h"

#include "dev/debug.h"
#include "js/js_game.h"

#include <iostream>

building_menu_ctrl_t g_building_menu_ctrl;
static building_menu_item building_menu_item_dummy{-1, false};

declare_console_command_p(update_menu) {
    std::string args;
    is >> args;
    g_building_menu_ctrl.update(args.c_str());
}

void ANK_REGISTER_CONFIG_ITERATOR(config_load_building_menu) {
    auto copy_config = g_building_menu_ctrl;
    g_config_arch.r_array("building_menu", g_building_menu_ctrl.groups, [&copy_config] (archive arch, auto &group) {
        group.type = arch.r_int("id");
        verify_no_crash(group.type != 0);
        arch.r_desc("anim", group.img);
        auto items = arch.r_array_num<int>("items");
        for (auto &it : items) {
            const bool enabled = copy_config.group(group.type).enabled(it);
            group.items.push_back({it, enabled});
        }
    });
}

bool building_menu_ctrl_t::is_submenu(int submenu) const {
    const bool is_group = (std::find_if(groups.begin(), groups.end(), [submenu](auto &gr) { return gr.type == submenu; }) != groups.end());
    return is_group;
}

void building_menu_ctrl_t::toggle_building(e_building_type type, bool enabled) {
    set(type, enabled);
    scenario_building_allow(type, enabled);

    // additional buildings / building menus
    if (enabled) {
        const auto &params = building_static_params::get(type);
        if (params.flags.is_farm) {
            toggle_building(BUILDING_MENU_FARMS);
        }

        if (params.flags.is_extractor || params.flags.is_harvester) {
            toggle_building(BUILDING_MENU_RAW_MATERIALS);
            toggle_building(BUILDING_MENU_INDUSTRY);
        }

        if (building_is_workshop(type)) {
            toggle_building(BUILDING_MENU_INDUSTRY);
        }

        if (params.flags.is_fort) {
            toggle_building(BUILDING_MENU_FORTS);
        }

        if (building_is_defense((e_building_type)type))
            toggle_building(BUILDING_MENU_DEFENSES);

        if (building_is_shrine((e_building_type)type))
            toggle_building(BUILDING_MENU_SHRINES);

        if (building_is_temple((e_building_type)type))
            toggle_building(BUILDING_MENU_TEMPLES);

        if (building_is_temple_complex((e_building_type)type))
            toggle_building(BUILDING_MENU_TEMPLE_COMPLEX);

        if (building_is_guild((e_building_type)type))
            toggle_building(BUILDING_MENU_CONSTURCTION_GUILDS);

        if (building_is_beautification((e_building_type)type))
            toggle_building(BUILDING_MENU_BEAUTIFICATION);

        if (building_is_water_crossing((e_building_type)type))
            toggle_building(BUILDING_MENU_WATER_CROSSINGS);

        if (params.flags.is_monument) {
            toggle_building(BUILDING_MENU_MONUMENTS);
        }

        if (params.flags.is_education) {
            toggle_building(BUILDING_MENU_EDUCATION);
        }
    }
}

void building_menu_ctrl_t::enable_if_allowed(e_building_type type) {
    const bool is_enabled = scenario_building_allowed(type);
    if (is_enabled) {
        toggle_building(type);
        logs::info("build_menu: enabled %d<%s> by config", type, e_building_type_tokens.name((e_building_type)type));
    }
}

int building_menu_ctrl_t::disable_raw_if_unavailable(int type, e_resource resource) {
    if (!g_city.can_produce_resource(resource)) {
        toggle_building((e_building_type)type, false);
        logs::info("build_menu: disabled %d<%s> by no resource", type, e_building_type_tokens.name((e_building_type)type));
        return 0;
    }
    return 1;
}

void building_menu_ctrl_t::disable_resources() {
    disable_raw_if_unavailable(BUILDING_BARLEY_FARM, RESOURCE_BARLEY);
    disable_raw_if_unavailable(BUILDING_FLAX_FARM, RESOURCE_FLAX);
    disable_raw_if_unavailable(BUILDING_GRAIN_FARM, RESOURCE_GRAIN);
    disable_raw_if_unavailable(BUILDING_LETTUCE_FARM, RESOURCE_LETTUCE);
    disable_raw_if_unavailable(BUILDING_POMEGRANATES_FARM, RESOURCE_POMEGRANATES);
    disable_raw_if_unavailable(BUILDING_CHICKPEAS_FARM, RESOURCE_CHICKPEAS);
    disable_raw_if_unavailable(BUILDING_FIGS_FARM, RESOURCE_FIGS);
    disable_raw_if_unavailable(BUILDING_HENNA_FARM, RESOURCE_HENNA);

    //
    disable_raw_if_unavailable(BUILDING_HUNTING_LODGE, RESOURCE_GAMEMEAT);
    disable_raw_if_unavailable(BUILDING_FISHING_WHARF, RESOURCE_FISH);

    //
    disable_raw_if_unavailable(BUILDING_CLAY_PIT, RESOURCE_CLAY);
    disable_raw_if_unavailable(BUILDING_WOOD_CUTTERS, RESOURCE_TIMBER);
    disable_raw_if_unavailable(BUILDING_REED_GATHERER, RESOURCE_REEDS);

    //
    disable_raw_if_unavailable(BUILDING_STONE_QUARRY, RESOURCE_STONE);
    disable_raw_if_unavailable(BUILDING_LIMESTONE_QUARRY, RESOURCE_LIMESTONE);
    disable_raw_if_unavailable(BUILDING_GRANITE_QUARRY, RESOURCE_GRANITE);
    disable_raw_if_unavailable(BUILDING_SANDSTONE_QUARRY, RESOURCE_SANDSTONE);
    disable_raw_if_unavailable(BUILDING_COPPER_MINE, RESOURCE_COPPER);
    disable_raw_if_unavailable(BUILDING_GEMSTONE_MINE, RESOURCE_GEMS);
    //
}

void building_menu_ctrl_t::enable_correct_palace_tier() {
    int rank = scenario_property_player_rank();
    if (rank < 6) {
        //
        toggle_building(BUILDING_TOWN_PALACE, false);
        toggle_building(BUILDING_CITY_PALACE, false);
        //
        toggle_building(BUILDING_FAMILY_MANSION, false);
        toggle_building(BUILDING_DYNASTY_MANSION, false);
    } else if (rank < 8) {
        toggle_building(BUILDING_VILLAGE_PALACE, false);
        //
        toggle_building(BUILDING_CITY_PALACE, false);
        toggle_building(BUILDING_PERSONAL_MANSION, false);
        //
        toggle_building(BUILDING_DYNASTY_MANSION, false);
    } else {
        toggle_building(BUILDING_VILLAGE_PALACE, false);
        toggle_building(BUILDING_TOWN_PALACE, false);
        //
        toggle_building(BUILDING_PERSONAL_MANSION, false);
        toggle_building(BUILDING_FAMILY_MANSION, false);
        //
    }
}

void building_menu_ctrl_t::enable_common_beautifications() {
    toggle_building(BUILDING_SMALL_STATUE);
    toggle_building(BUILDING_MEDIUM_STATUE);
    toggle_building(BUILDING_LARGE_STATUE);
    toggle_building(BUILDING_GARDENS);
    toggle_building(BUILDING_PLAZA);
}

void building_menu_ctrl_t::enable_common_municipal(int level) {
    enable_common_beautifications();
    toggle_building(BUILDING_ROADBLOCK);
    toggle_building(BUILDING_FIREHOUSE);
    toggle_building(BUILDING_ARCHITECT_POST);
    toggle_building(BUILDING_POLICE_STATION);
    toggle_building((level >= 3) ? BUILDING_CITY_PALACE : BUILDING_NONE);
    toggle_building((level >= 2) ? BUILDING_TOWN_PALACE : BUILDING_NONE);
    toggle_building((level >= 1) ? BUILDING_VILLAGE_PALACE : BUILDING_NONE);
}

void building_menu_ctrl_t::enable_common_health() {
    toggle_building(BUILDING_WATER_SUPPLY);
    toggle_building(BUILDING_APOTHECARY);
    toggle_building(BUILDING_PHYSICIAN);
}

void building_menu_ctrl_t::enable_entertainment(int level) {
    toggle_building((level >= 1) ? BUILDING_BOOTH : BUILDING_NONE);
    toggle_building((level >= 1) ? BUILDING_JUGGLER_SCHOOL : BUILDING_NONE);

    toggle_building((level >= 2) ? BUILDING_BANDSTAND : BUILDING_NONE);
    toggle_building((level >= 2) ? BUILDING_CONSERVATORY : BUILDING_NONE);

    toggle_building((level >= 3) ? BUILDING_PAVILLION : BUILDING_NONE);
    toggle_building((level >= 3) ? BUILDING_DANCE_SCHOOL : BUILDING_NONE);

    toggle_building((level >= 4) ? BUILDING_SENET_HOUSE : BUILDING_NONE);
}

struct god_buildings_alias {
    e_god god;
    e_building_type types[2];
};

god_buildings_alias god_buildings_aliases[] = {
    {GOD_OSIRIS,    {BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS}},
    {GOD_RA,        {BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA}},
    {GOD_PTAH,      {BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH}},
    {GOD_SETH,      {BUILDING_TEMPLE_SETH, BUILDING_SHRINE_SETH}},
    {GOD_BAST,      {BUILDING_TEMPLE_BAST, BUILDING_SHRINE_BAST}}
};

template<typename ... Args>
static void enable_gods(Args... args) {
    int mask = make_gods_mask(args...);
    int gods[] = {args...};

    g_building_menu_ctrl.toggle_building(BUILDING_FESTIVAL_SQUARE);
    for (auto &g : gods) {
        auto &buildings = god_buildings_aliases[g].types;
        for (auto &b : buildings) {
            g_building_menu_ctrl.toggle_building(b);
        }
    }
}

void building_menu_ctrl_t::update_gods_available(e_god god, bool available) {
    const auto &buildings = god_buildings_aliases[god].types;
    for (const auto &b : buildings) {
        toggle_building(b, available);
    }
}

void building_menu_ctrl_t::update_temple_complexes() {
    if (!!game_features::gameplay_change_multiple_temple_complexes) {
        return;
    }

    bool has_temple_complex = g_city.buildings.has_temple_complex();
    int temple_complex_id = g_city.buildings.temple_complex_id();

    if (has_temple_complex) {
        // can't build more than one
        for (const e_building_type type : g_city.buildings.temple_complex_types()) {
            set_visible(type, false);
        }

        // check if temple complex upgrades have been placed
        auto b = building_get_ex<building_temple_complex>(temple_complex_id);
        if (b) {
            const bool temple_has_altar = b && b->has_upgrade(etc_upgrade_altar);
            const auto &allowed_altar = b->base_params().allowed_altar;
            for (const auto &type : allowed_altar) {
                set_visible(type, !temple_has_altar);
            }

            const bool temple_has_oracle = b && b->has_upgrade(etc_upgrade_oracle);
            const auto &allowed_oracle = b->base_params().allowed_oracle;
            for (const auto &type : allowed_oracle) {
                set_visible(type, !temple_has_oracle);
            }

            // all upgrades have been placed!
            if (temple_has_altar && temple_has_oracle) {
                toggle_building(BUILDING_MENU_TEMPLE_COMPLEX, false);
            }
        }    

        // 
    } else {
        for (const e_building_type type : g_city.buildings.temple_complex_types()) {
            set_visible(type, true);
        }

        building_static_params::for_each([this] (auto &bsp) { 
            if (bsp.needs.altar || bsp.needs.oracle) {
                set_visible(bsp.type, false);
            }
        });
    }
}

void building_menu_update_monuments() {
}

image_desc building_menu_ctrl_t::image(int submenu) {
    const auto &gr = group(submenu);
    return gr.img;
}

void building_menu_ctrl_t::setup_mission() {
    set_all(false);
    update("stage_normal");
}

void building_menu_ctrl_t::register_callbacks() {
    events::subscribe([this] (event_building_menu_update ev) {
        update(ev.stage);
    });

    events::subscribe([this] (event_religion_god_status_update ev) {
        update_gods_available(ev.god, ev.status);
    });
}

void building_menu_ctrl_t::init() {
    set_all(true);
    register_callbacks();
}

void building_menu_ctrl_t::update(const xstring stage_name) {
    if (stage_name == tutorial_stage.disable_all) {
        set_all(false);
    } else if (stage_name == "stage_normal") {
        for (int i = 0; i < BUILDING_MAX; i++) {
            enable_if_allowed((e_building_type)i);
        }

        // enable monuments!
        building_menu_update_monuments();

        // update temple complexes
        update_temple_complexes();

        // disable resources that aren't available on map
        disable_resources();
    } else {
        verify_no_crash(false);
    }

    // disable government building tiers depending on mission rank
    enable_correct_palace_tier();

    // these are always enabled
    const auto &gr = group(BUILDING_MENU_DEFAULT);
    for (const auto &b: gr.items) {
        toggle_building((e_building_type)b.type);
    }

    events::emit(event_building_menu_changed{ true });
}

int building_menu_ctrl_t::count_items(int submenu) {
    auto &gr = group(submenu);
    int count = 0;
    for (auto &it : gr.items) {
        const auto group_it = std::find_if(groups.begin(), groups.end(), [type = it.type] (auto &gr) { return gr.type == type; });
        const bool is_group = (group_it != groups.end());
        if (is_group) {
            count += (count_items(it.type) > 0 ? 1 : 0);
        } else {
            count += (it.enabled ? 1 : 0);
        }
    }
    return count;
}

int building_menu_ctrl_t::next_index(int submenu, int current_index) {
    const auto &gr = group(submenu);
    for (int i = current_index + 1; i < gr.items.size(); i++) {
        if (gr.items[i].enabled)
            return i;
    }
    return 0;
}

building_menu_item &building_menu_group::dummy() {
    return building_menu_item_dummy;
}
