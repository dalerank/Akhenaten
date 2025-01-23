#include "building_menu.h"

#include "city/buildings.h"
#include "city/city.h"
#include "empire/empire.h"
#include "game/tutorial.h"
#include "config/config.h"
#include "scenario/scenario.h"

#include "core/archive.h"
#include "core/log.h"
#include "core/game_environment.h"
#include "io/gamefiles/lang.h"
#include "building/industry.h"

#include "dev/debug.h"
#include "js/js_game.h"

#include <iostream>

ANK_REGISTER_CONFIG_ITERATOR(config_load_buldingin_menu);

declare_console_command_p(menuupdate, game_cheat_menu_update);
void game_cheat_menu_update(std::istream &is, std::ostream &) {
    std::string args;
    is >> args;
    building_menu_update(args.c_str());
}

#define BUILD_MENU_ITEM_MAX 30

struct building_menu_item {
    int type = -1;
    bool enabled = false;
};

static building_menu_item building_menu_item_dummy{-1, false};
struct building_menu_group {
    using items_t = svector<building_menu_item, BUILD_MENU_ITEM_MAX>;

    building_menu_item &operator[](int type) {
        auto it = std::find_if(items.begin(), items.end(), [type] (auto &item) { return item.type == type; });
        return (it != items.end()) ? *it : building_menu_item_dummy;
    }

    void set_all(bool enabled) {
        for (auto &it : items) {
            it.enabled = enabled;
        }
    }

    inline bool enabled(int type) { return (*this)[type].enabled; }

    items_t::iterator begin() { return items.begin(); }
    items_t::iterator end() { return items.end(); }

    void clear() {
        items.clear();
    }

    animation_t anim;

    int type;
    items_t items;
};

struct menu_config_t {
    svector<building_menu_group, 30> groups;
    building_menu_group &group(int type) {
        static building_menu_group building_menu_group_dummy;
        auto it = std::find_if(groups.begin(), groups.end(), [type] (auto &it) { return it.type == type; });
        return (it != groups.end()) ? *it : building_menu_group_dummy;
    }

    void set(int type, bool enabled) {
        for (auto &group : groups) {
            auto &item = group[type];
            if (item.type == type) {
                item.enabled = enabled;
            }
        }
    }

    building_menu_item &get(int type) {
        for (auto &group : groups) {
            auto &item = group[type];
            if (item.type == type) {
                return item;
            }
        }

        assert(false && "should be exist type");
        return building_menu_item_dummy;
    }

    bool is_enabled(int type) {
        const building_menu_item &item = get(type);
        return (item.type == type) ? item.enabled : false;
    }

    int type(int submenu, int index) { 
        auto &gr = group(submenu);
        return (index < gr.items.size() ? gr.items[index].type : 0);
    }

    void set_all(bool enabled) {
        for (auto &group : groups) {
            group.set_all(enabled);
        }
    }

    void clear() {
        for (auto &gr : groups) {
            gr.clear();
        }
    }
    bool changed = true;
} g_menu_config;

void config_load_buldingin_menu() {
    auto copy_config = g_menu_config;
    g_config_arch.r_array("building_menu", g_menu_config.groups, [&copy_config] (archive arch, auto &group) {
        group.type = arch.r_int("id");
        assert(group.type != 0);
        arch.r_anim("anim", group.anim);
        auto items = arch.r_array_num<int>("items");
        for (auto &it : items) {
            const bool enabled = copy_config.group(group.type).enabled(it);
            group.items.push_back({it, enabled});
        }
    });
}

void building_menu_set_all(bool enabled) {
    g_menu_config.set_all(enabled);
}

bool building_menu_is_submenu(int submenu) {
    auto groups = g_menu_config.groups;
    const bool is_group = (std::find_if(groups.begin(), groups.end(), [submenu](auto &gr) { return gr.type == submenu; }) != groups.end());
    return is_group;
}

int building_menu_is_building_enabled(int type) {
    return g_menu_config.is_enabled(type);
}

void building_menu_toggle_building(int type, bool enabled) {
    g_menu_config.set(type, enabled);

    // additional buildings / building menus
    if (enabled) {
        if (building_is_farm((e_building_type)type)) {
            building_menu_toggle_building(BUILDING_MENU_FARMS);
        }

        if (building_is_extractor(type) || building_is_harvester((e_building_type)type)) {
            building_menu_toggle_building(BUILDING_MENU_RAW_MATERIALS);
            building_menu_toggle_building(BUILDING_MENU_INDUSTRY);
        }

        if (building_is_workshop(type)) {
            building_menu_toggle_building(BUILDING_MENU_INDUSTRY);
        }

        if (building_is_fort(type)) {
            building_menu_toggle_building(BUILDING_MENU_FORTS);
        }

        if (building_is_defense((e_building_type)type))
            building_menu_toggle_building(BUILDING_MENU_DEFENSES);

        if (building_is_shrine(type))
            building_menu_toggle_building(BUILDING_MENU_SHRINES);

        if (building_is_temple(type))
            building_menu_toggle_building(BUILDING_MENU_TEMPLES);

        if (building_is_large_temple(type))
            building_menu_toggle_building(BUILDING_MENU_TEMPLE_COMPLEX);

        if (building_is_guild((e_building_type)type))
            building_menu_toggle_building(BUILDING_MENU_CONSTURCTION_GUILDS);

        if (building_is_beautification((e_building_type)type))
            building_menu_toggle_building(BUILDING_MENU_BEAUTIFICATION);

        if (building_is_water_crossing((e_building_type)type))
            building_menu_toggle_building(BUILDING_MENU_WATER_CROSSINGS);

        if (building_is_monument((e_building_type)type))
            building_menu_toggle_building(BUILDING_MENU_MONUMENTS);

        if (building_is_education((e_building_type)type)) {
            building_menu_toggle_building(BUILDING_MENU_EDUCATION);
        }
    }
}

static void enable_if_allowed(int type) {
    const bool is_enabled = scenario_building_allowed(type);
    if (is_enabled) {
        building_menu_toggle_building(type);
        logs::info("build_menu: enabled %d<%s> by config", type, e_building_type_tokens.name((e_building_type)type));
    }
}

static int disable_raw_if_unavailable(int type, e_resource resource) {
    if (!g_city.can_produce_resource(resource)) {
        building_menu_toggle_building(type, false);
        logs::info("build_menu: disabled %d<%s> by no resource", type, e_building_type_tokens.name((e_building_type)type));
        return 0;
    }
    return 1;
}

static int disable_crafted_if_unavailable(int type, e_resource resource, e_resource resource2 = RESOURCE_NONE) {
    if (!g_city.can_produce_resource(resource)) {
        building_menu_toggle_building(type, false);
        return 0;
    }

    if (resource2 != RESOURCE_NONE && !g_city.can_produce_resource(resource2)) {
        building_menu_toggle_building(type, false);
        return 0;
    }
    return 1;
}

static void disable_resources() {
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

    //disable_crafted_if_unavailable(BUILDING_POTTERY_WORKSHOP, RESOURCE_POTTERY);
    //disable_crafted_if_unavailable(BUILDING_BREWERY_WORKSHOP, RESOURCE_BEER);
    //disable_crafted_if_unavailable(BUILDING_JEWELS_WORKSHOP, RESOURCE_LUXURY_GOODS);
    //disable_crafted_if_unavailable(BUILDING_WEAVER_WORKSHOP, RESOURCE_LINEN);
    //disable_crafted_if_unavailable(BUILDING_PAPYRUS_WORKSHOP, RESOURCE_PAPYRUS);
    //disable_crafted_if_unavailable(BUILDING_BRICKS_WORKSHOP, RESOURCE_BRICKS, RESOURCE_STRAW);
    //disable_crafted_if_unavailable(BUILDING_CATTLE_RANCH, RESOURCE_MEAT, RESOURCE_STRAW);
    //disable_crafted_if_unavailable(BUILDING_WEAPONSMITH, RESOURCE_WEAPONS);
    //disable_crafted_if_unavailable(BUILDING_CHARIOTS_WORKSHOP, RESOURCE_CHARIOTS);
    //
    //disable_crafted_if_unavailable(BUILDING_PAINT_WORKSHOP, RESOURCE_PAINT);
    //disable_crafted_if_unavailable(BUILDING_LAMP_WORKSHOP, RESOURCE_LAMPS);
}

static void enable_correct_palace_tier() {
    int rank = scenario_property_player_rank();
    if (rank < 6) {
        //
        building_menu_toggle_building(BUILDING_TOWN_PALACE, false);
        building_menu_toggle_building(BUILDING_CITY_PALACE, false);
        //
        building_menu_toggle_building(BUILDING_FAMILY_MANSION, false);
        building_menu_toggle_building(BUILDING_DYNASTY_MANSION, false);
    } else if (rank < 8) {
        building_menu_toggle_building(BUILDING_VILLAGE_PALACE, false);
        //
        building_menu_toggle_building(BUILDING_CITY_PALACE, false);
        building_menu_toggle_building(BUILDING_FAMILY_MANSION, false);
        //
        building_menu_toggle_building(BUILDING_DYNASTY_MANSION, false);

    } else {
        building_menu_toggle_building(BUILDING_VILLAGE_PALACE, false);
        building_menu_toggle_building(BUILDING_TOWN_PALACE, false);
        //
        building_menu_toggle_building(BUILDING_PERSONAL_MANSION, false);
        building_menu_toggle_building(BUILDING_FAMILY_MANSION, false);
        //
    }
}

static void enable_common_beautifications() {
    building_menu_toggle_building(BUILDING_SMALL_STATUE);
    building_menu_toggle_building(BUILDING_MEDIUM_STATUE);
    building_menu_toggle_building(BUILDING_LARGE_STATUE);
    building_menu_toggle_building(BUILDING_GARDENS);
    building_menu_toggle_building(BUILDING_PLAZA);
}

static void enable_common_municipal(int level) {
    enable_common_beautifications();
    building_menu_toggle_building(BUILDING_ROADBLOCK);
    building_menu_toggle_building(BUILDING_FIREHOUSE);
    building_menu_toggle_building(BUILDING_ARCHITECT_POST);
    building_menu_toggle_building(BUILDING_POLICE_STATION);
    building_menu_toggle_building((level >= 3) | BUILDING_CITY_PALACE);
    building_menu_toggle_building((level >= 2) | BUILDING_TOWN_PALACE);
    building_menu_toggle_building((level >= 1) | BUILDING_VILLAGE_PALACE);
}

static void enable_common_health() {
    building_menu_toggle_building(BUILDING_WATER_SUPPLY);
    building_menu_toggle_building(BUILDING_APOTHECARY);
    building_menu_toggle_building(BUILDING_PHYSICIAN);
}

static void enable_entertainment(int level) {
    building_menu_toggle_building((level >= 1) | BUILDING_BOOTH);
    building_menu_toggle_building((level >= 1) | BUILDING_JUGGLER_SCHOOL);

    building_menu_toggle_building((level >= 2) | BUILDING_BANDSTAND);
    building_menu_toggle_building((level >= 2) | BUILDING_CONSERVATORY);

    building_menu_toggle_building((level >= 3) | BUILDING_PAVILLION);
    building_menu_toggle_building((level >= 3) | BUILDING_DANCE_SCHOOL);

    building_menu_toggle_building((level >= 4) | BUILDING_SENET_HOUSE);
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

    building_menu_toggle_building(BUILDING_FESTIVAL_SQUARE);
    for (auto &g : gods) {
        auto &buildings = god_buildings_aliases[g].types;
        for (auto &b : buildings) {
            building_menu_toggle_building(b);
        }
    }
}

void building_menu_update_gods_available(e_god god, bool available) {
    auto &buildings = god_buildings_aliases[god].types;
    for (auto &b : buildings) {
        building_menu_toggle_building(b, available);
    }
}

void building_menu_update_temple_complexes() {
    if (!config_get(CONFIG_GP_CH_MULTIPLE_TEMPLE_COMPLEXES)) {
        if (city_buildings_has_temple_complex()) {
            // can't build more than one
            building_menu_toggle_building(BUILDING_TEMPLE_COMPLEX_OSIRIS, false);
            building_menu_toggle_building(BUILDING_TEMPLE_COMPLEX_RA, false);
            building_menu_toggle_building(BUILDING_TEMPLE_COMPLEX_PTAH, false);
            building_menu_toggle_building(BUILDING_TEMPLE_COMPLEX_SETH, false);
            building_menu_toggle_building(BUILDING_TEMPLE_COMPLEX_BAST, false);

            // check if upgrades have been placed
            building* b = building_get(city_buildings_get_temple_complex());
            if (b->data.monuments.temple_complex_attachments & 2) // altar
                building_menu_toggle_building(BUILDING_TEMPLE_COMPLEX_ALTAR, false);
            else
                building_menu_toggle_building(BUILDING_TEMPLE_COMPLEX_ALTAR, true);
            if (b->data.monuments.temple_complex_attachments & 1) // oracle
                building_menu_toggle_building(BUILDING_TEMPLE_COMPLEX_ORACLE, false);
            else
                building_menu_toggle_building(BUILDING_TEMPLE_COMPLEX_ORACLE, true);

            // all upgrades have been placed!
            if (b->data.monuments.temple_complex_attachments == 1 + 2)
                building_menu_toggle_building(BUILDING_MENU_TEMPLE_COMPLEX, false);

        } else {
            enable_if_allowed(BUILDING_TEMPLE_COMPLEX_OSIRIS);
            enable_if_allowed(BUILDING_TEMPLE_COMPLEX_RA);
            enable_if_allowed(BUILDING_TEMPLE_COMPLEX_PTAH);
            enable_if_allowed(BUILDING_TEMPLE_COMPLEX_SETH);
            enable_if_allowed(BUILDING_TEMPLE_COMPLEX_BAST);

            building_menu_toggle_building(BUILDING_TEMPLE_COMPLEX_ALTAR, false);
            building_menu_toggle_building(BUILDING_TEMPLE_COMPLEX_ORACLE, false);
        }
    } else {
        // TODO...?
    }
}

void building_menu_update_monuments() {
}

const animation_t &building_menu_anim(int submenu) {
    auto &group = g_menu_config.group(submenu);
    return group.anim;
}

void building_menu_setup_mission() {
    building_menu_set_all(false);
    building_menu_update("stage_normal");
}

void building_menu_update(const xstring stage_name) {
    if (stage_name == tutorial_stage.disable_all) {
        building_menu_set_all(false);
    } else if (stage_name == "stage_normal") {
        for (int i = 0; i < BUILDING_MAX; i++) {
            enable_if_allowed(i);
        }

        // enable monuments!
        building_menu_update_monuments();

        // update temple complexes
        building_menu_update_temple_complexes();

        // disable resources that aren't available on map
        disable_resources();
    } else {
        for (const auto &stage : g_scenario_data.building_stages) {
            if (stage.key == stage_name) {
                for (const auto &b : stage.buildings) {
                    building_menu_toggle_building(b);
                }
            }
        }
    }

    // disable government building tiers depending on mission rank
    enable_correct_palace_tier();

    // these are always enabled
    building_menu_toggle_building(BUILDING_HOUSE_VACANT_LOT);
    building_menu_toggle_building(BUILDING_CLEAR_LAND);
    building_menu_toggle_building(BUILDING_ROAD);
    building_menu_toggle_building(BUILDING_WELL);

    g_menu_config.changed = 1;
}

int building_menu_count_items(int submenu) {
    auto &group = g_menu_config.group(submenu);
    int count = 0;
    auto groups = g_menu_config.groups;
    for (auto &it : group.items) {
        const auto group_it = std::find_if(groups.begin(), groups.end(), [type = it.type] (auto &gr) { return gr.type == type; });
        const bool is_group = (group_it != groups.end());
        if (is_group) {
            count += (building_menu_count_items(it.type) > 0 ? 1 : 0);
        } else {
            count += (it.enabled ? 1 : 0);
        }
    }
    return count;
}

int building_menu_next_index(int submenu, int current_index) {
    auto &group = g_menu_config.group(submenu);
    for (int i = current_index + 1; i < group.items.size(); i++) {
        if (group.items[i].enabled)
            return i;
    }
    return 0;
}

e_building_type building_menu_type(int submenu, int item) {
    return (e_building_type)g_menu_config.type(submenu, item);
}

bool building_menu_has_changed() {
    if (g_menu_config.changed) {
        g_menu_config.changed = false;
        return true;
    }
    return false;
}

void building_menu_invalidate() {
    g_menu_config.changed = true;
}
