#include "building.h"

#include "building/building_type.h"
#include "scenario/scenario_data.h"

bool scenario_building_allowed(int building_type) {
    switch (building_type) {
    case BUILDING_GOLD_MINE:
        return g_scenario_data.allowed_buildings[2];
    case BUILDING_WATER_LIFT:
        return g_scenario_data.allowed_buildings[3];
    case BUILDING_IRRIGATION_DITCH:
        return g_scenario_data.allowed_buildings[4];
    case BUILDING_SHIPYARD:
        return g_scenario_data.allowed_buildings[5];
    case BUILDING_WORK_CAMP:
        return g_scenario_data.allowed_buildings[6];
    case BUILDING_GRANARY:
        return g_scenario_data.allowed_buildings[7];
    case BUILDING_MARKET:
        return g_scenario_data.allowed_buildings[8];
    case BUILDING_STORAGE_YARD:
        return g_scenario_data.allowed_buildings[9];
    case BUILDING_DOCK:
        return g_scenario_data.allowed_buildings[10];
    case BUILDING_BOOTH:
    case BUILDING_JUGGLER_SCHOOL:
        return g_scenario_data.allowed_buildings[11];
    case BUILDING_BANDSTAND:
    case BUILDING_CONSERVATORY:
        return g_scenario_data.allowed_buildings[12];
    case BUILDING_PAVILLION:
    case BUILDING_DANCE_SCHOOL:
        return g_scenario_data.allowed_buildings[13];
    case BUILDING_SENET_HOUSE:
        return g_scenario_data.allowed_buildings[14];
    case BUILDING_FESTIVAL_SQUARE:
        return g_scenario_data.allowed_buildings[15];
    case BUILDING_SCRIBAL_SCHOOL:
        return g_scenario_data.allowed_buildings[16];
    case BUILDING_LIBRARY:
        return g_scenario_data.allowed_buildings[17];
    case BUILDING_WATER_SUPPLY:
        return g_scenario_data.allowed_buildings[18];
    case BUILDING_DENTIST:
        return g_scenario_data.allowed_buildings[19];
    case BUILDING_APOTHECARY:
        return g_scenario_data.allowed_buildings[20];
    case BUILDING_PHYSICIAN:
        return g_scenario_data.allowed_buildings[21];
    case BUILDING_MORTUARY:
        return g_scenario_data.allowed_buildings[22];
    case BUILDING_TAX_COLLECTOR:
        return g_scenario_data.allowed_buildings[23];
    case BUILDING_COURTHOUSE:
        return g_scenario_data.allowed_buildings[24];
    case BUILDING_VILLAGE_PALACE:
    case BUILDING_TOWN_PALACE:
    case BUILDING_CITY_PALACE:
        return g_scenario_data.allowed_buildings[25];
    case BUILDING_PERSONAL_MANSION:
    case BUILDING_FAMILY_MANSION:
    case BUILDING_DYNASTY_MANSION:
        return g_scenario_data.allowed_buildings[26];
    case BUILDING_ROADBLOCK:
        return g_scenario_data.allowed_buildings[27];
    case BUILDING_LOW_BRIDGE:
        return g_scenario_data.allowed_buildings[28];
    case BUILDING_FERRY:
        return g_scenario_data.allowed_buildings[29];
    case BUILDING_GARDENS:
        return g_scenario_data.allowed_buildings[30];
    case BUILDING_PLAZA:
        return g_scenario_data.allowed_buildings[31];
    case BUILDING_SMALL_STATUE:
    case BUILDING_MEDIUM_STATUE:
    case BUILDING_LARGE_STATUE:
        return g_scenario_data.allowed_buildings[32];
    case BUILDING_WALL_PH:
        return g_scenario_data.allowed_buildings[33];
    case BUILDING_TOWER_PH:
        return g_scenario_data.allowed_buildings[34];
    case BUILDING_GATEHOUSE_PH:
        return g_scenario_data.allowed_buildings[35];
    case BUILDING_RECRUITER:
        return g_scenario_data.allowed_buildings[36];
    case BUILDING_FORT_INFANTRY:
        return g_scenario_data.allowed_buildings[37];
    case BUILDING_FORT_ARCHERS:
        return g_scenario_data.allowed_buildings[38];
    case BUILDING_FORT_CHARIOTEERS:
        return g_scenario_data.allowed_buildings[39];
    case BUILDING_MILITARY_ACADEMY:
        return g_scenario_data.allowed_buildings[40];
    case BUILDING_WEAPONS_WORKSHOP:
        return g_scenario_data.allowed_buildings[41];
    case BUILDING_CHARIOTS_WORKSHOP:
        return g_scenario_data.allowed_buildings[42];
    case BUILDING_WARSHIP_WHARF:
        return g_scenario_data.allowed_buildings[43];
    case BUILDING_TRANSPORT_WHARF:
        return g_scenario_data.allowed_buildings[44];
    case BUILDING_ZOO:
        return g_scenario_data.allowed_buildings[45];
        ///
    case BUILDING_TEMPLE_COMPLEX_OSIRIS:
        return g_scenario_data.allowed_buildings[104];
    case BUILDING_TEMPLE_COMPLEX_RA:
        return g_scenario_data.allowed_buildings[105];
    case BUILDING_TEMPLE_COMPLEX_PTAH:
        return g_scenario_data.allowed_buildings[106];
    case BUILDING_TEMPLE_COMPLEX_SETH:
        return g_scenario_data.allowed_buildings[107];
    case BUILDING_TEMPLE_COMPLEX_BAST:
        return g_scenario_data.allowed_buildings[108];
    }
    return true;
}

int scenario_building_image_native_hut(void) {
    return g_scenario_data.native_images.hut;
}

int scenario_building_image_native_meeting(void) {
    return g_scenario_data.native_images.meeting;
}

int scenario_building_image_native_crops(void) {
    return g_scenario_data.native_images.crops;
}
