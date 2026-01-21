#pragma once

#include "core/archive.h"
#include "game/resource.h"
#include "grid/desirability.h"
#include "grid/crime.h"

class building;
class building_juggler_school;
class building_storage_yard;
class building_storage_room;
class building_brewery;
class building_pottery;
class building_bazaar;
class building_firehouse;
class building_architect_post;
class building_booth;
class building_apothecary;
class building_granary;
class building_water_supply;
class building_conservatory;
class building_courthouse;
class building_well;
class building_clay_pit;
class building_reed_gatherer;
class building_papyrus_maker;
class building_dock;
class building_mastaba;
class building_small_mastaba;
class building_medium_mastaba;
class building_wood_cutter;
class building_work_camp;
class building_recruiter;
class building_pavilion;
class building_statue;
class building_ferry;
class building_farm;
class building_fort;
class building_fort_ground;
class building_fishing_wharf;
class building_warship_wharf;
class building_shipyard;
class building_plaza;
class building_garden;
class building_house;
class building_burning_ruin;
class building_storage;
class building_temple;
class building_tax_collector;
class building_roadblock;
class building_mine;
class building_quarry;
class building_palace;
class building_festival_square;
class building_bandstand;
class building_routeblock;
class building_industry;
class building_guild;
class building_entertainment;
class building_mansion;
class building_physician;
class building_wharf;
class building_shrine;
class building_transport_wharf;
class building_temple_complex;
class building_temple_complex_altar;
class building_temple_complex_oracle;
class building_water_lift;
class building_monument;
class building_scribal_school;
class building_tower;
class building_senet_house;
class building_gatehouse;
class building_dancer_school;
class building_police_station;
class building_dentist;
class building_mortuary;
class building_pyramid;
class building_small_stepped_pyramid;
class building_medium_stepped_pyramid;

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
};
ANK_CONFIG_STRUCT(building_flags_rule,
    is_monument, is_extractor, is_harvester, is_farm, is_fort, is_education, is_palace, is_temple,
    is_shrine, is_tax_collector, is_statue, is_administration, is_water_crossing, is_infrastructure,
    is_beautification, is_guild, is_industry, is_workshop, is_house, is_wall, is_defense)

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
    uint16_t help_id;
    uint16_t text_id;
    xstring help_link;
};
ANK_CONFIG_STRUCT(metainfo, help_id, text_id, help_link)

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