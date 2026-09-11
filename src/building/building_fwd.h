#pragma once

#include "core/archive.h"
#include "game/resource.h"
#include "grid/desirability.h"
#include "grid/crime.h"

class building;

// Every building class reachable through dcast<T>() is listed here once. This list drives the
// forward declarations below, the smart_cast specialisations in building_cast.h, the dcast_x()
// shorthands on building, and the virtual dcast_x() hooks on building_impl -- four lists that
// used to be written out by hand and had already drifted apart.
#define BUILDING_CLASS_LIST(X) \
    X(farm)                    \
    X(juggler_school)          \
    X(storage_yard)            \
    X(storage_room)            \
    X(brewery)                 \
    X(pottery)                 \
    X(bazaar)                  \
    X(firehouse)               \
    X(booth)                   \
    X(granary)                 \
    X(water_supply)            \
    X(conservatory)            \
    X(courthouse)              \
    X(well)                    \
    X(clay_pit)                \
    X(reed_gatherer)           \
    X(papyrus_maker)           \
    X(dock)                    \
    X(mastaba)                 \
    X(small_mastaba)           \
    X(medium_mastaba)          \
    X(large_mastaba)           \
    X(wood_cutter)             \
    X(recruiter)               \
    X(pavilion)                \
    X(statue)                  \
    X(ferry)                   \
    X(fort)                    \
    X(fort_ground)             \
    X(fishing_wharf)           \
    X(warship_wharf)           \
    X(shipyard)                \
    X(plaza)                   \
    X(garden)                  \
    X(house)                   \
    X(burning_ruin)            \
    X(storage)                 \
    X(temple)                  \
    X(tax_collector)           \
    X(roadblock)               \
    X(mine)                    \
    X(quarry)                  \
    X(palace)                  \
    X(festival_square)         \
    X(bandstand)               \
    X(routeblock)              \
    X(industry)                \
    X(guild)                   \
    X(entertainment)           \
    X(mansion)                 \
    X(physician)               \
    X(wharf)                   \
    X(shrine)                  \
    X(transport_wharf)         \
    X(temple_complex)          \
    X(temple_complex_altar)    \
    X(temple_complex_oracle)   \
    X(water_lift)              \
    X(monument)                \
    X(scribal_school)          \
    X(tower)                   \
    X(senet_house)             \
    X(gatehouse)               \
    X(work_camp)               \
    X(dancer_school)           \
    X(police_station)          \
    X(dentist)                 \
    X(mortuary)                \
    X(pyramid)                 \
    X(small_stepped_pyramid)   \
    X(medium_stepped_pyramid)  \
    X(sphinx)                  \
    X(obelisk)                 \
    X(sun_temple)              \
    X(abu_simbel)              \
    X(caesareum)               \
    X(alexandria_library)      \
    X(mausoleum)               \
    X(pharos_lighthouse)       \
    X(royal_tomb)              \
    X(food_mill)               \
    X(industry_office)

#define BUILDING_FWD_DECLARE(name) class building_##name;
BUILDING_CLASS_LIST(BUILDING_FWD_DECLARE)
#undef BUILDING_FWD_DECLARE

// Declared but not castable: these have no dcast_x() of their own and are reached through the
// base they share (pyramid, royal_tomb, mastaba, temple_complex).
class building_large_stepped_pyramid;
class building_stepped_pyramid_complex;
class building_grand_stepped_pyramid_complex;
class building_small_bent_pyramid;
class building_medium_bent_pyramid;
class building_small_pyramid;
class building_medium_pyramid;
class building_large_pyramid;
class building_pyramid_complex;
class building_grand_pyramid_complex;
class building_small_mudbrick_pyramid;
class building_medium_mudbrick_pyramid;
class building_large_mudbrick_pyramid;
class building_mudbrick_pyramid_complex;
class building_grand_mudbrick_pyramid_complex;
class building_small_royal_tomb;
class building_medium_royal_tomb;
class building_large_royal_tomb;
class building_grand_royal_tomb;

using e_building_need_rules = uint32_t;

struct building_planner_need_rule {
    bool meadow;
    bool rock;
    bool ore;
    bool altar;
    bool oracle;
    bool nearby_water;
    bool groundwater;
    bool shoreline;
    bool canals;
    bool floodplain_shoreline;
    bool water_access;
};
ANK_CONFIG_STRUCT(building_planner_need_rule, meadow, rock, ore, altar, oracle,
    nearby_water, groundwater, shoreline, canals, floodplain_shoreline, water_access)

struct building_flags_rule {
    bool is_monument;
    bool is_extractor;
    bool is_harvester;
    bool is_farm;
    bool is_fort;
    bool is_education;
    bool is_palace;
    bool is_temple;
    bool is_shrine;
    bool is_tax_collector;
    bool is_statue;
    bool is_administration;
    bool is_water_crossing;
    bool is_infrastructure;
    bool is_beautification;
    bool is_guild;
    bool is_industry;
    bool is_workshop;
    bool is_house;
    bool is_wall;
    bool is_defense;
    bool is_temple_complex;
    bool is_religion;
    bool is_military;
    bool is_entertainment;
    bool is_food;
    bool allow_rotate;
    bool no_road_access;
    bool non_deletable;
    bool keeps_visitor_paths;
    bool perimeter_access;
    bool draw_normal_anim;
    bool work_anim;
};
ANK_CONFIG_STRUCT(building_flags_rule,
    is_monument, is_extractor, is_harvester, is_farm, is_fort, is_education, is_palace, is_temple,
    is_shrine, is_tax_collector, is_statue, is_administration, is_water_crossing, is_infrastructure,
    is_beautification, is_guild, is_industry, is_workshop, is_house, is_wall, is_defense, is_temple_complex,
    is_religion, is_military, is_entertainment, is_food, allow_rotate, no_road_access, non_deletable,
    keeps_visitor_paths, perimeter_access, draw_normal_anim, work_anim)

struct building_crime_t {
    svector<int8_t, 6> value;
    svector<int8_t, 6> step;
    svector<int8_t, 6> step_size;
    svector<int8_t, 6> range;

    crime_t::influence_t to_influence() const;
};
ANK_CONFIG_STRUCT(building_crime_t, value, step, step_size, range)

enum e_building_state : uint8_t {
    BUILDING_STATE_UNUSED = 0,
    BUILDING_STATE_VALID = 1,
    BUILDING_STATE_UNDO = 2,
    BUILDING_STATE_CREATED = 3,
    BUILDING_STATE_RUBBLE = 4,
    BUILDING_STATE_DELETED_BY_GAME = 5, // used for earthquakes, fires, house mergers
    BUILDING_STATE_DELETED_BY_PLAYER = 6,
    BUILDING_STATE_MOTHBALLED = 7,
    BUILDING_STATE_COUNT,
};
extern const token_holder<e_building_state, BUILDING_STATE_UNUSED, BUILDING_STATE_COUNT> e_building_state_tokens;

enum e_building_slot {
    BUILDING_SLOT_SERVICE = 0,
    BUILDING_SLOT_CARTPUSHER = 1,
    BUILDING_SLOT_MARKET_BUYER = 1,
    BUILDING_SLOT_LABOR_SEEKER = 2,
    BUILDING_SLOT_MARKET_BUYER_2 = 3,
    BUILDING_SLOT_JUGGLER = 0,
    BUILDING_SLOT_DRUNKARD = 1,
    BUILDING_SLOT_MUSICIAN = 1,
    BUILDING_SLOT_DANCER = 2,
    BUILDING_SLOT_PRIEST = 2,
    BUILDING_SLOT_IMMIGRANT = 2,
    BUILDING_SLOT_HOMELESS = 2,
    BUILDING_SLOT_GOVERNOR = 3,
    BUILDING_SLOT_HUNTER = 3,
    BUILDING_SLOT_BOAT = 3,
    BUILDING_SLOT_BALLISTA = 3,
    BUILDING_SLOT_CARTPUSHER_2 = 3,
};


struct building_desirability_t {
    svector<int8_t, 6> value;
    svector<int8_t, 6> step;
    svector<int8_t, 6> step_size;
    svector<int8_t, 6> range;

    desirability_t::influence_t to_influence() const;
};
ANK_CONFIG_STRUCT(building_desirability_t, value, step, step_size, range)

struct building_input {
    e_resource resource;
    e_resource resource_second;
};
using building_output = building_input;
ANK_CONFIG_STRUCT(building_input, resource, resource_second)

struct metainfo {
    uint16_t text_id;
    xstring help_link;
};
ANK_CONFIG_STRUCT(metainfo, text_id, help_link)

struct building_planner_update_rule {
    bool canals;
    bool roads;
    bool ferries;
    bool is_draggable;
    int relative_orientation;
    bool unique_building;
};
ANK_CONFIG_STRUCT(building_planner_update_rule, 
    canals, roads, ferries, is_draggable, relative_orientation, unique_building)
