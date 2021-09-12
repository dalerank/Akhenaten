#include "building.h"

#include "building/building_state.h"
#include "building/properties.h"
#include "building/rotation.h"
#include "building/storage.h"
#include "city/buildings.h"
#include "city/population.h"
#include "city/warning.h"
#include "figure/formation_legion.h"
#include "game/resource.h"
#include "game/undo.h"
#include "map/building_tiles.h"
#include "map/desirability.h"
#include "map/elevation.h"
#include "map/grid.h"
#include "map/random.h"
#include "map/routing_terrain.h"
#include "map/terrain.h"
#include "map/tiles.h"
#include "menu.h"
#include "monuments.h"

#include <string.h>
#include <map/building.h>

static building all_buildings[5000];

static struct {
    int highest_id_in_use;
    int highest_id_ever;
    int created_sequence;
//    int incorrect_houses;
//    int unfixable_houses;
} extra = {0, 0, 0};

int building_find(int type) {
    for (int i = 1; i < MAX_BUILDINGS[GAME_ENV]; ++i) {
        building *b = building_get(i);
        if (b->state == BUILDING_STATE_VALID && b->type == type)
            return i;

    }
    return MAX_BUILDINGS[GAME_ENV];
}
building *building_get(int id) {
    return &all_buildings[id];
}

static void building_new_fill_in_data_for_type(building *b, int type, int x, int y, int orientation) {
    const building_properties *props = building_properties_for_type(type);
    b->state = BUILDING_STATE_CREATED;
    b->faction_id = 1;
    b->unknown_value = city_buildings_unknown_value();
    b->type = type;
    b->size = props->size;
    b->creation_sequence_index = extra.created_sequence++;
    b->sentiment.house_happiness = 50;
    b->distance_from_entry = 0;

    b->x = x;
    b->y = y;
    b->grid_offset = map_grid_offset(x, y);
    b->map_random_7bit = map_random_get(b->grid_offset) & 0x7f;
    b->figure_roam_direction = b->map_random_7bit & 6;
    b->fire_proof = props->fire_proof;
    b->is_adjacent_to_water = map_terrain_is_adjacent_to_water(x, y, b->size);

    // house size
    b->house_size = 0;
    if (type >= BUILDING_HOUSE_SMALL_TENT && type <= BUILDING_HOUSE_MEDIUM_INSULA)
        b->house_size = 1;
    else if (type >= BUILDING_HOUSE_LARGE_INSULA && type <= BUILDING_HOUSE_MEDIUM_VILLA)
        b->house_size = 2;
    else if (type >= BUILDING_HOUSE_LARGE_VILLA && type <= BUILDING_HOUSE_MEDIUM_PALACE)
        b->house_size = 3;
    else if (type >= BUILDING_HOUSE_LARGE_PALACE && type <= BUILDING_HOUSE_LUXURY_PALACE)
        b->house_size = 4;

    // subtype
    if (b->is_house())
        b->subtype.house_level = type - BUILDING_HOUSE_VACANT_LOT;
    else
        b->subtype.house_level = 0;

    // unique data
    if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        switch (type) {
            case BUILDING_BARLEY_FARM:
                b->output_resource_id = RESOURCE_BARLEY;
                break;
            case BUILDING_FLAX_FARM:
                b->output_resource_id = RESOURCE_FLAX;
                break;
            case BUILDING_GRAIN_FARM:
                b->output_resource_id = RESOURCE_GRAIN;
                break;
            case BUILDING_LETTUCE_FARM:
                b->output_resource_id = RESOURCE_LETTUCE;
                break;
            case BUILDING_POMEGRANATES_FARM:
                b->output_resource_id = RESOURCE_POMEGRANATES;
                break;
            case BUILDING_CHICKPEAS_FARM:
                b->output_resource_id = RESOURCE_CHICKPEAS;
                break;
            case BUILDING_STONE_QUARRY:
                b->output_resource_id = RESOURCE_STONE;
                break;
            case BUILDING_LIMESTONE_QUARRY:
                b->output_resource_id = RESOURCE_LIMESTONE;
                break;
            case BUILDING_TIMBER_YARD:
                b->output_resource_id = RESOURCE_TIMBER_PH;
                break;
            case BUILDING_CLAY_PIT:
                b->output_resource_id = RESOURCE_CLAY;
                break;
            case BUILDING_BEER_WORKSHOP:
                b->output_resource_id = RESOURCE_BEER;
                b->subtype.workshop_type = WORKSHOP_VINES_TO_WINE; // todo
                break;
            case BUILDING_LINEN_WORKSHOP:
                b->output_resource_id = RESOURCE_LINEN;
                b->subtype.workshop_type = WORKSHOP_OLIVES_TO_OIL; // todo
                break;
            case BUILDING_WEAPONS_WORKSHOP:
                b->output_resource_id = RESOURCE_WEAPONS_C3;
                b->subtype.workshop_type = WORKSHOP_IRON_TO_WEAPONS; // todo
                break;
            case BUILDING_JEWELS_WORKSHOP:
                b->output_resource_id = RESOURCE_LUXURY_GOODS;
                b->subtype.workshop_type = WORKSHOP_TIMBER_TO_FURNITURE; // todo
                break;
            case BUILDING_POTTERY_WORKSHOP:
                b->output_resource_id = RESOURCE_POTTERY_PH;
                b->subtype.workshop_type = WORKSHOP_CLAY_TO_POTTERY;
                break;
            case BUILDING_HUNTING_LODGE:
                b->output_resource_id = RESOURCE_GAMEMEAT;
                break;
            case BUILDING_REED_GATHERER:
                b->output_resource_id = RESOURCE_REEDS;
                break;
            case BUILDING_GOLD_MINE:
                b->output_resource_id = RESOURCE_GOLD;
                break;
            case BUILDING_GEMSTONE_MINE:
                b->output_resource_id = RESOURCE_GEMS;
                break;
            case BUILDING_CATTLE_RANCH:
                b->output_resource_id = RESOURCE_MEAT_PH;
//                b->subtype.workshop_type = ??? todo
                break;
            case BUILDING_FIGS_FARM:
                b->output_resource_id = RESOURCE_FIGS;
                break;
            case BUILDING_PAPYRUS_WORKSHOP:
                b->output_resource_id = RESOURCE_PAPYRUS;
                b->subtype.workshop_type = WORKSHOP_REEDS_TO_PAPYRUS;
                break;
            case BUILDING_BRICKS_WORKSHOP:
                b->output_resource_id = RESOURCE_BRICKS;
//                b->subtype.workshop_type = ??? todo
                break;
            case BUILDING_CHARIOTS_WORKSHOP:
                b->output_resource_id = RESOURCE_CHARIOTS;
//                b->subtype.workshop_type = ??? todo
                break;
            case BUILDING_GRANITE_QUARRY:
                b->output_resource_id = RESOURCE_GRANITE;
                break;
            case BUILDING_COPPER_MINE:
                b->output_resource_id = RESOURCE_COPPER;
                break;
            case BUILDING_SANDSTONE_QUARRY:
                b->output_resource_id = RESOURCE_SANDSTONE;
                break;
            case BUILDING_HENNA_FARM:
                b->output_resource_id = RESOURCE_HENNA;
                break;
            case BUILDING_LAMP_WORKSHOP:
                b->output_resource_id = RESOURCE_LAMPS;
//                b->subtype.workshop_type = ??? todo
                break;
            case BUILDING_PAINT_WORKSHOP:
                b->output_resource_id = RESOURCE_PAINT;
//                b->subtype.workshop_type = ??? todo
                break;
            case BUILDING_GRANARY:
                b->data.granary.resource_stored[RESOURCE_NONE] = 3200;
                b->storage_id = building_storage_create(BUILDING_GRANARY);
                break;
            case BUILDING_MARKET: // Set it as accepting all goods
                b->subtype.market_goods = 0x0000;
                break;
            case BUILDING_WAREHOUSE:
                b->subtype.orientation = building_rotation_get_rotation();
                break;
            case BUILDING_SMALL_STATUE:
            case BUILDING_MEDIUM_STATUE:
            case BUILDING_LARGE_STATUE:
                b->data.monuments.variant = get_statue_variant_value((4 + building_rotation_get_rotation() + city_view_orientation() / 2) % 4, building_rotation_get_building_variant());
                break;
            case BUILDING_TEMPLE_COMPLEX_OSIRIS:
            case BUILDING_TEMPLE_COMPLEX_RA:
            case BUILDING_TEMPLE_COMPLEX_PTAH:
            case BUILDING_TEMPLE_COMPLEX_SETH:
            case BUILDING_TEMPLE_COMPLEX_BAST:
                b->data.monuments.variant = (10 - (2 * orientation)) % 8; // ugh!
                break;
            case BUILDING_WATER_LIFT:
            case BUILDING_FISHING_WHARF:
            case BUILDING_TRANSPORT_WHARF:
            case BUILDING_SHIPYARD:
            case BUILDING_WARSHIP_WHARF:
            case BUILDING_FERRY:
                b->data.industry.orientation = orientation;
                break;
            case BUILDING_DOCK:
                b->data.dock.orientation = orientation;
                break;
            case BUILDING_GATEHOUSE_PH:
            case BUILDING_GATEHOUSE:
                b->subtype.orientation = orientation;
                break;
            default:
                b->output_resource_id = RESOURCE_NONE;
                break;
        }
    }
}
building *building_create(int type, int x, int y, int orientation) {
    building *b = 0;
    for (int i = 1; i < MAX_BUILDINGS[GAME_ENV]; i++) {
        if (all_buildings[i].state == BUILDING_STATE_UNUSED && !game_undo_contains_building(i)) {
            b = &all_buildings[i];
            break;
        }
    }
    if (!b) {
        city_warning_show(WARNING_DATA_LIMIT_REACHED);
        return &all_buildings[0];
    }
    memset(&(b->data), 0, sizeof(b->data));
    building_new_fill_in_data_for_type(b, type, x, y, orientation);
    return b;
}

building *building_at(int grid_offset) {
    return building_get(map_building_at(grid_offset));
}
building *building_at(int x, int y) {
    return building_get(map_building_at(map_grid_offset(x, y)));
}
building *building_at(map_point point) {
    return building_get(map_building_at(map_grid_offset(point.x, point.y)));
}
bool building_exists_at(int grid_offset, building *b) {
    b = nullptr;
    int b_id = map_building_at(grid_offset);
    if (b_id > 0) {
        b = building_get(b_id);
        if (b->state > BUILDING_STATE_UNUSED)
            return true;
        else
            b = nullptr;
    }
    return false;
}
bool building_exists_at(int x, int y, building *b) {
    b = nullptr;
    int b_id = map_building_at(map_grid_offset(x, y));
    if (b_id > 0) {
        b = building_get(b_id);
        if (b->state > BUILDING_STATE_UNUSED)
            return true;
        else
            b = nullptr;
    }
    return false;
}
bool building_exists_at(map_point point, building *b) {
    b = nullptr;
    int b_id = map_building_at(map_grid_offset(point.x, point.y));
    if (b_id > 0) {
        b = building_get(b_id);
        if (b->state > BUILDING_STATE_UNUSED)
            return true;
        else
            b = nullptr;
    }
    return false;
}

building *building::main() {
    building *b = this;
    for (int guard = 0; guard < 99; guard++) {
        if (b->prev_part_building_id <= 0)
            return b;
        b = &all_buildings[b->prev_part_building_id];
    }
    return &all_buildings[0];
}
building *building::top_xy() {
    building *b = main();
    int x = b->x;
    int y = b->y;
    building *top = b;
    while (b->next_part_building_id <= 0) {
        b = next();
        if (b->x < x)
            top = b;
        if (b->y < y)
            top = b;
    }
    return top;
}
building *building::next() {
    return building_get(next_part_building_id);
}
bool building::is_main() {
    return (prev_part_building_id == 0);
}

static void building_delete_UNSAFE(building *b) {
    b->clear_related_data();
    int id = b->id;
    memset(b, 0, sizeof(building));
    b->id = id;
}
void building::clear_related_data() {
    if (storage_id)
        building_storage_delete(storage_id);

    if (is_senate())
        city_buildings_remove_palace(this);

    if (is_governor_palace())
        city_buildings_remove_mansion(this);

    if (type == BUILDING_DOCK)
        city_buildings_remove_dock();

    if (type == BUILDING_RECRUITER)
        city_buildings_remove_recruiter(this);

    if (type == BUILDING_DISTRIBUTION_CENTER_UNUSED)
        city_buildings_remove_distribution_center(this);

    if (type == BUILDING_MENU_FORTS)
        formation_legion_delete_for_fort(this);

    if (type == BUILDING_SENET_HOUSE)
        city_buildings_remove_hippodrome();

    if (type == BUILDING_TRIUMPHAL_ARCH) {
        city_buildings_remove_triumphal_arch();
        building_menu_update(BUILDSET_NORMAL);
    }

    if (type == BUILDING_FESTIVAL_SQUARE)
        city_buildings_remove_festival_square();
}
void building_clear_all(void) {
    for (int i = 0; i < MAX_BUILDINGS[GAME_ENV]; i++) {
        memset(&all_buildings[i], 0, sizeof(building));
        all_buildings[i].id = i;
    }
    extra.highest_id_in_use = 0;
    extra.highest_id_ever = 0;
    extra.created_sequence = 0;
//    extra.incorrect_houses = 0;
//    extra.unfixable_houses = 0;
}
//void building_totals_add_corrupted_house(int unfixable)
//{
//    extra.incorrect_houses++;
//    if (unfixable) {
//        extra.unfixable_houses++;
//    }
//}

bool building::is_house() {
    return building_is_house(type);
}
bool building::is_fort() {
    return building_is_fort(type);
}
bool building::is_defense_ph() {
    return building_is_defense_ph(type);
}
bool building::is_farm() {
    return building_is_farm(type);
}
bool building::is_floodplain_farm() {
    return building_is_floodplain_farm(this);
}
bool building::is_workshop() {
    return building_is_workshop(type);
}
bool building::is_extractor() {
    return building_is_extractor(type);
}
bool building::is_monument() {
    return building_is_monument(type);
}
bool building::is_senate() {
    return building_is_senate(type);
}
bool building::is_tax_collector() {
    return building_is_tax_collector(type);
}
bool building::is_governor_palace() {
    return building_is_governor_palace(type);
}
bool building::is_temple() {
    return building_is_temple(type);
}
bool building::is_large_temple() {
    return building_is_large_temple(type);
}
bool building::is_shrine() {
    return building_is_shrine(type);
}
bool building::is_guild() {
    return building_is_guild(type);
}
bool building::is_beautification() {
    return building_is_beautification(type);
}
bool building::is_water_crossing() {
    return building_is_water_crossing(type);
}

bool building::is_industry() {
    return building_is_industry(type);
}
bool building::is_food_category() {
    return building_is_food_category(type);
}
bool building::is_infrastructure() {
    return building_is_infrastructure(type);
}
bool building::is_administration() {
    return building_is_administration(type);
}
bool building::is_religion() {
    return building_is_religion(type);
}
bool building::is_entertainment() {
    return building_is_entertainment(type);
}
bool building::is_culture() {
    return building_is_culture(type);
}
bool building::is_military() {
    return building_is_military(type);
}

///////////////

bool building_is_house(int type) {
    return type >= BUILDING_HOUSE_VACANT_LOT && type <= BUILDING_HOUSE_LUXURY_PALACE;
}
bool building_is_fort(int type) {
    return type == BUILDING_FORT_CHARIOTEERS ||
           type == BUILDING_FORT_ARCHERS ||
           type == BUILDING_FORT_INFANTRY;
}
bool building_is_defense_ph(int type) {
    return (type == BUILDING_WALL_PH
            || type == BUILDING_GATEHOUSE_PH
            || type == BUILDING_TOWER_PH);
}
bool building_is_farm(int type) {
    return (type >= BUILDING_BARLEY_FARM && type <= BUILDING_CHICKPEAS_FARM)
           || type == BUILDING_FIGS_FARM || type == BUILDING_HENNA_FARM;
}
bool building_is_floodplain_farm(const building *b) {
    return (GAME_ENV == ENGINE_ENV_PHARAOH
            && building_is_farm(b->type)
            && map_terrain_is(b->grid_offset, TERRAIN_FLOODPLAIN)); // b->data.industry.labor_state >= 1 // b->labor_category == 255
}
bool building_is_workshop(int type) {
    return (type >= BUILDING_BEER_WORKSHOP && type <= BUILDING_POTTERY_WORKSHOP)
           || (type >= BUILDING_PAPYRUS_WORKSHOP && type <= BUILDING_CHARIOTS_WORKSHOP)
           || type == BUILDING_CATTLE_RANCH
           || type == BUILDING_LAMP_WORKSHOP
           || type == BUILDING_PAINT_WORKSHOP;
}
bool building_is_extractor(int type) {
    return (type >= BUILDING_STONE_QUARRY && type <= BUILDING_CLAY_PIT)
           || type == BUILDING_GOLD_MINE
           || type == BUILDING_GEMSTONE_MINE
           || type == BUILDING_COPPER_MINE
           || type == BUILDING_GRANITE_QUARRY
           || type == BUILDING_SANDSTONE_QUARRY
           || type == BUILDING_REED_GATHERER;
}
bool building_is_monument(int type) {
    switch (type) {
        case BUILDING_PYRAMID:
        case BUILDING_SPHYNX:
        case BUILDING_MAUSOLEUM:
        case BUILDING_ALEXANDRIA_LIBRARY:
        case BUILDING_CAESAREUM:
        case BUILDING_PHAROS_LIGHTHOUSE:
        case BUILDING_SMALL_ROYAL_TOMB:
        case BUILDING_ABU_SIMBEL:
        case BUILDING_MEDIUM_ROYAL_TOMB:
        case BUILDING_LARGE_ROYAL_TOMB:
        case BUILDING_GRAND_ROYAL_TOMB:
            return true;
        default:
            return false;
    }
}
bool building_is_senate(int type) {
    return ((type >= BUILDING_SENATE && type <= BUILDING_TAX_COLLECTOR_UPGRADED) ||
            (type >= BUILDING_VILLAGE_PALACE && type <= BUILDING_CITY_PALACE));
}
bool building_is_tax_collector(int type) {
    return (type >= BUILDING_TAX_COLLECTOR && type <= BUILDING_TAX_COLLECTOR_UPGRADED);
}
bool building_is_governor_palace(int type) {
    return (type >= BUILDING_PERSONAL_MANSION && type <= BUILDING_DYNASTY_MANSION);
}
bool building_is_temple(int type) {
    return (type >= BUILDING_TEMPLE_OSIRIS && type <= BUILDING_TEMPLE_BAST);
}
bool building_is_large_temple(int type) {
    return (type >= BUILDING_TEMPLE_COMPLEX_OSIRIS && type <= BUILDING_TEMPLE_COMPLEX_BAST);
}
bool building_is_shrine(int type) {
    return (type >= BUILDING_SHRINE_OSIRIS && type <= BUILDING_SHRINE_BAST);
}
bool building_is_guild(int type) {
    return (type >= BUILDING_CARPENTERS_GUILD && type <= BUILDING_STONEMASONS_GUILD);
}
bool building_is_statue(int type) {
    return (type >= BUILDING_SMALL_STATUE && type <= BUILDING_LARGE_STATUE);
}
bool building_is_beautification(int type) {
    return building_is_statue(type)
           || type == BUILDING_GARDENS
           || type == BUILDING_PLAZA;
}
bool building_is_water_crossing(int type) {
    return (type == BUILDING_FERRY)
           || type == BUILDING_LOW_BRIDGE
           || type == BUILDING_SHIP_BRIDGE;
}
bool building_is_industry_type(const building *b) {
    return b->output_resource_id || b->type == BUILDING_NATIVE_CROPS
           || b->type == BUILDING_SHIPYARD || b->type == BUILDING_FISHING_WHARF;
}

bool building_is_industry(int type) {
    if (building_is_extractor(type))
        return true;
    if (building_is_workshop(type))
        return true;
    if (building_is_farm(type))
        return true;
    if (building_is_guild(type))
        return true;
    if (type == BUILDING_DOCK || type == BUILDING_SHIPYARD)
        return true;
    if (type == BUILDING_WAREHOUSE || type == BUILDING_WAREHOUSE_SPACE)
        return true;
    return false;
}
bool building_is_food_category(int type) {
    if (type == BUILDING_GRANARY || type == BUILDING_MARKET || type == BUILDING_WORK_CAMP
        || type == BUILDING_FISHING_WHARF || type == BUILDING_CATTLE_RANCH || type == BUILDING_HUNTING_LODGE)
        return true;
    return false;
}
bool building_is_infrastructure(int type) {
    if (type == BUILDING_ENGINEERS_POST || type == BUILDING_FIREHOUSE || type == BUILDING_POLICE_STATION)
        return true;
    if (building_is_water_crossing(type))
        return true;
    return false;
}
bool building_is_administration(int type) {
    if (building_is_senate(type) || building_is_tax_collector(type) || building_is_governor_palace(type))
        return true;
    if (type == BUILDING_COURTHOUSE)
        return true;
    return false;
}
bool building_is_religion(int type) {
    if (building_is_temple(type) || building_is_large_temple(type) || building_is_shrine(type))
        return true;
    if (type == BUILDING_FESTIVAL_SQUARE)
        return true;
    return false;
}
bool building_is_entertainment(int type) {
    if (type == BUILDING_BOOTH || type == BUILDING_BANDSTAND || type == BUILDING_PAVILLION)
        return true;
    if (type == BUILDING_JUGGLER_SCHOOL || type == BUILDING_CONSERVATORY || type == BUILDING_DANCE_SCHOOL)
        return true;
    if (type == BUILDING_SENET_HOUSE || type == BUILDING_ZOO)
        return true;
    return false;
}
bool building_is_culture(int type) {
    if (type == BUILDING_SCHOOL || type == BUILDING_LIBRARY || type == BUILDING_MENU_WATER_CROSSINGS)
        return true;
    return false;
}
bool building_is_military(int type) {
    if (building_is_fort(type) || type == BUILDING_FORT_GROUND || type == BUILDING_MENU_FORTS)
        return true;
    if (type == BUILDING_MILITARY_ACADEMY || type == BUILDING_RECRUITER)
        return true;
    return false;
}

bool building_is_draggable(int type) {
    switch (type) {
        case BUILDING_CLEAR_LAND:
        case BUILDING_ROAD:
        case BUILDING_IRRIGATION_DITCH:
        case BUILDING_WALL:
        case BUILDING_PLAZA:
        case BUILDING_GARDENS:
        case BUILDING_HOUSE_VACANT_LOT:
            return true;
        case BUILDING_WATER_LIFT:
//            if (GAME_ENV == ENGINE_ENV_C3)
//                return true;
//            else
            return false;
        default:
            return false;
    }
}

int building_get_highest_id(void) {
    return extra.highest_id_in_use;
}
void building_update_highest_id(void) {
    extra.highest_id_in_use = 0;
    for (int i = 1; i < MAX_BUILDINGS[GAME_ENV]; i++) {
        if (all_buildings[i].state != BUILDING_STATE_UNUSED)
            extra.highest_id_in_use = i;
    }
    if (extra.highest_id_in_use > extra.highest_id_ever)
        extra.highest_id_ever = extra.highest_id_in_use;
}
void building_update_state(void) {
    bool land_recalc = false;
    bool wall_recalc = false;
    bool road_recalc = false;
    bool aqueduct_recalc = false;
    for (int i = 1; i < MAX_BUILDINGS[GAME_ENV]; i++) {
        building *b = &all_buildings[i];
        if (b->state == BUILDING_STATE_CREATED)
            b->state = BUILDING_STATE_VALID;

        if (b->state != BUILDING_STATE_VALID || !b->house_size) {
            if (b->state == BUILDING_STATE_UNDO || b->state == BUILDING_STATE_DELETED_BY_PLAYER) {
                if (b->type == BUILDING_TOWER || b->type == BUILDING_GATEHOUSE) {
                    wall_recalc = true;
                    road_recalc = true;
                } else if (b->type == BUILDING_WATER_LIFT)
                    aqueduct_recalc = true;
                else if (b->type == BUILDING_GRANARY)
                    road_recalc = true;

                map_building_tiles_remove(i, b->x, b->y);
                road_recalc = true; // always recalc underlying road tiles
                land_recalc = true;
                building_delete_UNSAFE(b);
            } else if (b->state == BUILDING_STATE_RUBBLE) {
                if (b->house_size)
                    city_population_remove_home_removed(b->house_population);

                building_delete_UNSAFE(b);
            } else if (b->state == BUILDING_STATE_DELETED_BY_GAME)
                building_delete_UNSAFE(b);

        }
    }
    if (wall_recalc)
        map_tiles_update_all_walls();

    if (aqueduct_recalc)
        map_tiles_update_all_aqueducts(0);

    if (land_recalc)
        map_routing_update_land();

    if (road_recalc)
        map_tiles_update_all_roads();

}
void building_update_desirability(void) {
    for (int i = 1; i < MAX_BUILDINGS[GAME_ENV]; i++) {
        building *b = &all_buildings[i];
        if (b->state != BUILDING_STATE_VALID)
            continue;

        b->desirability = map_desirability_get_max(b->x, b->y, b->size);
        if (b->is_adjacent_to_water)
            b->desirability += 10;

        switch (map_elevation_at(b->grid_offset)) {
            case 0:
                break;
            case 1:
                b->desirability += 10;
                break;
            case 2:
                b->desirability += 12;
                break;
            case 3:
                b->desirability += 14;
                break;
            case 4:
                b->desirability += 16;
                break;
            default:
                b->desirability += 18;
                break;
        }
    }
}

int building_mothball_toggle(building *b) {
    if (b->state == BUILDING_STATE_VALID) {
        b->state = BUILDING_STATE_MOTHBALLED;
        b->num_workers = 0;
    } else if (b->state == BUILDING_STATE_MOTHBALLED)
        b->state = BUILDING_STATE_VALID;

    return b->state;

}
int building_mothball_set(building *b, int mothball) {
    if (mothball) {
        if (b->state == BUILDING_STATE_VALID) {
            b->state = BUILDING_STATE_MOTHBALLED;
            b->num_workers = 0;
        }
    } else if (b->state == BUILDING_STATE_MOTHBALLED)
        b->state = BUILDING_STATE_VALID;

    return b->state;

}

void building_save_state(buffer *buf, buffer *highest_id, buffer *highest_id_ever) {
    for (int i = 0; i < MAX_BUILDINGS[GAME_ENV]; i++) {
        building_state_save_to_buffer(buf, &all_buildings[i]);
    }
    highest_id->write_i32(extra.highest_id_in_use);
    highest_id_ever->write_i32(extra.highest_id_ever);
    highest_id_ever->skip(4);
//    sequence->write_i32(extra.created_sequence);

//    corrupt_houses->write_i32(extra.incorrect_houses);
//    corrupt_houses->write_i32(extra.unfixable_houses);
}
void building_load_state(buffer *buf, buffer *highest_id, buffer *highest_id_ever) {
    for (int i = 0; i < MAX_BUILDINGS[GAME_ENV]; i++) {
        if (!buf->is_valid(1))
            break;
        building_state_load_from_buffer(buf, &all_buildings[i]);
        all_buildings[i].id = i;
    }
    extra.highest_id_in_use = highest_id->read_i32();
    extra.highest_id_ever = highest_id_ever->read_i32();
    highest_id_ever->skip(4);
    extra.created_sequence = 0;
//    extra.created_sequence = sequence->read_i32();

//    extra.incorrect_houses = corrupt_houses->read_i32();
//    extra.unfixable_houses = corrupt_houses->read_i32();
}
