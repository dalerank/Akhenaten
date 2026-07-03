#pragma once

#include <cstdint>
#include "core/xstring.h"

struct event_mission_briefing_show_after_load { int scenario_id; };

struct mission_step_t;

struct mission_id_t {
    int _id;
    xstring _data;
    inline mission_id_t(int id) {
        _id = id;
        _data.printf("mission%d", id);
    }

    inline operator const char *() const { return _data.c_str(); }
    inline const xstring &value() const { return _data; }
};

constexpr int MAX_MISSION_CHOICE_BRANCHES = 5;
constexpr int MAX_MISSION_CAMPAIGNS = 10;

// Loaded from campaign.txt; path_ids are legacy branch markers (unused at runtime).
struct mission_step_t {
    int scenario_id = -1;
    int intro_MM = -1;
    int victory_text_id = -1;
    int path_ids[MAX_MISSION_CHOICE_BRANCHES] = {-1};
    const uint8_t* map_name;
    bool is_campaign_end = false;
    int campaign_id = -1;
    int mission_rank = -1;
    mission_step_t* previous_in_list = nullptr;
    mission_step_t* next_in_list = nullptr;
};

enum {
    SCENARIO_NULL = -1,

    // PREDYNASTIC -- PHARAOH
    SCENARIO_NUBT = 0,
    SCENARIO_THINIS_1 = 1,
    SCENARIO_PERWADJYT = 2,
    // ARCHAIC
    SCENARIO_NEKHEN = 3,
    SCENARIO_MEN_NEFER = 4,
    SCENARIO_TIMNA = 5,
    SCENARIO_BEHDET = 6,
    SCENARIO_ABEDJU = 7,
    // OLD KINGDOM
    SCENARIO_SELIMA_OASIS = 8,
    SCENARIO_ABU = 9,
    SCENARIO_SAQQARA = 10,
    SCENARIO_SERABIT_KHADIM = 11,
    SCENARIO_MEIDUM = 12,
    SCENARIO_BUHEN = 13,
    SCENARIO_SOUTH_DASHUR = 14,
    SCENARIO_NORTH_DASHUR = 15,
    SCENARIO_IUNET = 16,
    SCENARIO_ON = 17,
    SCENARIO_ROSTJA = 18,
    SCENARIO_BAHARIYA_OASIS = 19,
    SCENARIO_DJEDU = 20,
    SCENARIO_DAKHLA_OASIS = 21,
    SCENARIO_DUNQUL_OASIS = 22,
    // MIDDLE KINGDOM
    SCENARIO_THINIS_2 = 23,
    SCENARIO_WASET = 24,
    SCENARIO_KEBET = 25,
    SCENARIO_MENAT_KHUFU = 26,
    SCENARIO_ITJTAWY = 27,
    SCENARIO_IKEN = 28,
    SCENARIO_SAWU = 29,
    SCENARIO_HEH = 30,
    SCENARIO_BUBASTIS = 31,
    // NEW KINGDOM
    SCENARIO_KHMUN = 32,
    SCENARIO_SAUTY = 33,
    SCENARIO_BYBLOS = 34,
    SCENARIO_BAKI = 35,
    SCENARIO_ROWARTY = 36,
    SCENARIO_HETEPSENUSRET = 37,

    // VALLEY OF THE KINGS -- CLEOPATRA
    SCENARIO_VALLEY_THUTMOSE = 38,
    SCENARIO_VALLEY_TUT = 39,
    SCENARIO_VALLEY_SETI = 40,
    // RAMSES II
    SCENARIO_SUMUR = 41,
    SCENARIO_QADESH = 42,
    SCENARIO_ABU_SIMBEL = 43,
    SCENARIO_RAMSES_IN_THE_VALLEY = 44,
    // ANCIENT CONQUERORS
    SCENARIO_PI_YER = 45,
    SCENARIO_MIGDOL = 46,
    SCENARIO_TANIS = 47,
    // CLEOPATRA'S CAPITAL
    SCENARIO_ALEXANDRIA_1 = 48,
    SCENARIO_ALEXANDRIA_2 = 49,
    SCENARIO_MARITIS = 50,
    SCENARIO_ALEXANDRIA_3 = 51,
    SCENARIO_ACTIUM = 52,

    SCENARIO_MAX = 100
};

enum {
    CAMPAIGN_NULL = -1,
    //
    CAMPAIGN_PHARAOH_PREDYNASTIC = 0,
    CAMPAIGN_PHARAOH_ARCHAIC = 1,
    CAMPAIGN_PHARAOH_OLD_KINGDOM = 2,
    CAMPAIGN_PHARAOH_MIDDLE_KINGDOM = 3,
    CAMPAIGN_PHARAOH_NEW_KINGDOM = 4,
    //
    CAMPAIGN_CLEOPATRA_VALLEY_OF_THE_KINGS = 5,
    CAMPAIGN_CLEOPATRA_RAMSES_II = 6,
    CAMPAIGN_CLEOPATRA_ANCIENT_CONQUERORS = 7,
    CAMPAIGN_CLEOPATRA_CLEOPATRAS_CAPITAL = 8,
    //
    CAMPAIGN_MAX = MAX_MISSION_CAMPAIGNS
};

const uint8_t* game_mission_get_name(int scenario_id);
const mission_step_t* get_campaign_mission_step_data(int campaign_id, int step_index);
const mission_step_t* get_scenario_step_data(int scenario_id);

int get_scenario_campaign_id(int scenario_id);
int get_first_mission_in_campaign(int campaign_id);

bool game_scenario_beaten(int scenario_id);

bool game_load_campaign_file();
