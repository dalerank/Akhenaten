#include "mission.h"

#include "scenario/property.h"
#include "core/game_environment.h"

static const struct {
    int peaceful;
    int military;
} MISSION_IDS_C3[12] = {
        {0,  0},
        {1,  1},
        {2,  3},
        {4,  5},
        {6,  7},
        {8,  9},
        {10, 11},
        {12, 13},
        {14, 15},
        {16, 17},
        {18, 19},
        {20, 21},
}, MISSION_IDS_PH[23] = {
        // PREDYNASTIC
        {0,  0},    // 0 Nubt
        {1,  1},    // 1 Thinis
        {2,  2},    // 2 Perwadjyt
        // ARCHAIC
        {3,  3},    // 3 Nekhen
        {4,  4},    // 4 Men-nefer
        {5,  5},    // 5 Timna
        {7,  6},    // 6 Behdet  --- Abedju
        // OLD KINGDOM
        {9,  8},    // 7 Selima  --- Abu
        {10, 10},   // 8 Saqqara
        {12, 11},   // 9 Serabit --- Meidum
        {14, 13},   // 10 S.Dash. --- Buhen
        {15, 15},   // 11 North Dashur
        {17, 16},   // 12 Djedu   --- Bahariya
        {19, 18},   // 13 Dakhla  --- Dunqul
        // MIDDLE KINGDOM
        {21, 20},   // 14 Waset  --- Thinis
        {23, 22},   // 15 Menat Khufu --- Kebet
        {24, 24},   // 16 Itjtawy
        {26, 27},   // 17 Sawu    --- Iken
        {28, 29},   // 18 Bubastis --- Heh
        // NEW KINGDOM
        {31, 30},   // 19 Sauty   --- Khmun
        {33, 32},   // 20 Baki    --- Byblos
        {35, 35},   // 21 Hetepsenusret
        {34, 34},   // 22 Rowarty
};

static const int RANK_CHOICE_C3[] = {
        0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};
static const int MISSION_CHOICE_PH[22] = {
        0, 0, 0,
        0, 0, 1,
        1, 0, 1, 1, 0, 1, 1,
        1, 1, 0, 1, 1,
        1, 1, 0, 0
};
static const int MISSION_SELECTORS_BY_MISSION_PH[] = {
        1, 2, 3,
        4, 5, 6, 7, 7,
        8, 8, 9, 10, 10, 11, 11, 12, 13, 13, 14, 14,
        15, 15, 16, 16, 17, 18, 18, 19, 19,
        20, 20, 21, 22,
};

int scenario_ph_mission_selector() {
    return MISSION_SELECTORS_BY_MISSION_PH[scenario_campaign_mission()];
}
int game_mission_peaceful(void) {
    if (GAME_ENV == ENGINE_ENV_C3)
        return MISSION_IDS_C3[scenario_campaign_rank()].peaceful;
    else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        int selector = scenario_ph_mission_selector();
        return MISSION_IDS_PH[selector].peaceful;
    }
}
int game_mission_military(void) {
    if (GAME_ENV == ENGINE_ENV_C3)
        return MISSION_IDS_C3[scenario_campaign_rank()].military;
    else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        int selector = scenario_ph_mission_selector();
        return MISSION_IDS_PH[selector].military;
    }
}
int game_mission_has_choice(void) {
    if (GAME_ENV == ENGINE_ENV_C3)
        return RANK_CHOICE_C3[scenario_campaign_rank()];
    else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        int selector = scenario_ph_mission_selector();
        return MISSION_CHOICE_PH[selector];
    }
}