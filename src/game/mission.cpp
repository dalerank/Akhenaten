#include <core/file.h>
#include <core/buffer.h>
#include <core/io.h>
#include <core/log.h>
#include <core/string.h>
#include "mission.h"

#include "scenario/property.h"
#include "core/game_environment.h"
#include "player_data.h"

int get_mission_campaign_id(int scenario_id) {
    if (scenario_id < SCENARIO_NULL || scenario_id >= SCENARIO_MAX)
        return CAMPAIGN_NULL;
    for (int i = 0; i < 9; ++i) {
        int last_in_campaign = get_last_mission_in_campaign(i);
        if (scenario_id <= last_in_campaign)
            return i;
    }
}
int get_first_mission_in_campaign(int campaign_id) {
    if (campaign_id < CAMPAIGN_PHARAOH_PREDYNASTIC || campaign_id >= CAMPAIGN_MAX)
        return SCENARIO_NULL;
    if (campaign_id == CAMPAIGN_PHARAOH_PREDYNASTIC)
        return SCENARIO_NUBT;
    else
        return 1 + SCENARIO_LAST_IN_CAMPAIGN[campaign_id - 1];
}
int get_last_mission_in_campaign(int campaign_id) {
    if (campaign_id < CAMPAIGN_PHARAOH_PREDYNASTIC || campaign_id >= CAMPAIGN_MAX)
        return SCENARIO_NULL;

   return SCENARIO_LAST_IN_CAMPAIGN[campaign_id];
}

int game_mission_choose(int rank, int index) {
    if (index < 0 || index > 2)
        index = 0;
    const int *scenarios = MISSION_RANK_TO_SCENARIO[rank].scenario;
    if (scenarios[index] == SCENARIO_NULL)
        return scenarios[0];
    return scenarios[index];
}
bool game_mission_has_choice(void) {
    return false; // TODO
//    if (GAME_ENV == ENGINE_ENV_C3)
//        return RANK_CHOICE_C3[scenario_campaign_rank()];
//    else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
//        int selector = scenario_ph_mission_selector();
//        return CAN_CHOOSE_NEXT_SCENARIO_PH[selector];
//    }
}

bool game_campaign_unlocked(int campaign_id) {
    switch (campaign_id) {
        // pharaoh
        case CAMPAIGN_PHARAOH_ARCHAIC:
            return game_scenario_unlocked(SCENARIO_NUBT);
        case CAMPAIGN_PHARAOH_PREDYNASTIC:
            return game_scenario_unlocked(SCENARIO_NEKHEN);
        case CAMPAIGN_PHARAOH_OLD_KINGDOM:
            return game_scenario_unlocked(SCENARIO_SELIMA_OASIS);
        case CAMPAIGN_PHARAOH_MIDDLE_KINGDOM:
            return game_scenario_unlocked(SCENARIO_THINIS_2);
        case CAMPAIGN_PHARAOH_NEW_KINGDOM:
            return game_scenario_unlocked(SCENARIO_KHMUN);
        // cleopatra
        case CAMPAIGN_CLEOPATRA_VALLEY_OF_THE_KINGS:
            return game_scenario_unlocked(SCENARIO_VALLEY_THUTMOSE);
        case CAMPAIGN_CLEOPATRA_RAMSES_II:
            return game_scenario_unlocked(SCENARIO_SUMUR);
        case CAMPAIGN_CLEOPATRA_ANCIENT_CONQUERORS:
            return game_scenario_unlocked(SCENARIO_PI_YER);
        case CAMPAIGN_CLEOPATRA_CLEOPATRAS_CAPITAL:
            return game_scenario_unlocked(SCENARIO_ALEXANDRIA_1);
    }
}
bool game_scenario_unlocked(int scenario_id) {
    if (scenario_id < 0 || scenario_id >= SCENARIO_MAX) // invalid mission index
        return false;
    switch (scenario_id) {
        case SCENARIO_NUBT:
        case SCENARIO_VALLEY_THUTMOSE:
            return true; // first mission is always unlocked
    }
    const int *requirements = SCENARIO_REQUIREMENTS_PH[scenario_id].req_beaten;
    // by default, beating the previous scenario will unlock the scenario.
    if (requirements[0] == SCENARIO_NULL)
        return game_scenario_beaten(scenario_id - 1);
    // if otherwise specified, this scenario requires specific ones to unlock;
    // any one of them in the req. group will suffice to unlock the scenario.
    for (int i = 0; i < 3; ++i) {
        if (requirements[i] != SCENARIO_NULL)
            if (game_scenario_beaten(requirements[i]))
                return true;
    }
}
bool game_scenario_beaten(int scenario_id) {
    if (scenario_id < 0 || scenario_id >= SCENARIO_MAX) // invalid mission index
        return false;
    auto record = player_get_scenario_record(scenario_id);
    return record->nonempty;
}

struct {
    uint8_t map_names[300][300];
    int map_name_nums = 0;

    struct {
        struct {
            int type; // 0 = mission; 1 = choice; 2 = end campaign
            struct {
                int scenario_id = -1;
                int intro_MM;
                int victory_text_id;
                int path_ids[5];
//                int num_paths = 0;
            } mission;
            struct {
                int graphics_id;
                int text_id;
                struct {
                    int path_id;
                    int x;
                    int y;
                    int text_id;
                } branches[5];
                int num_branches = 0;
            } choice;
        } steps[50];
        int num_steps = 0;
    } campaigns[10];
    int num_campaigns = 0;
} data;

const uint8_t *game_mission_get_name(int scenario_id) {
    if (scenario_id >= data.map_name_nums || scenario_id > 299)
        return data.map_names[0];
    return data.map_names[scenario_id];
}

#define TMP_BUFFER_SIZE 10000
static const uint8_t *CAMPAIGN_FILE_BEGIN = string_from_ascii("\n[MISSION_NAMES]\n");
static const uint8_t *skip_non_digits(const uint8_t *str) {
    int safeguard = 0;
    while (1) {
        if (++safeguard >= 1000)
            break;

        if ((*str >= '0' && *str <= '9') || *str == '-')
            break;

        str++;
    }
    return str;
}
static const uint8_t *get_value(const uint8_t *ptr, const uint8_t *end_ptr, int *value) {
    ptr = skip_non_digits(ptr);
    *value = string_to_int(ptr);
    int skip = index_of(ptr, ',', (int) (end_ptr - ptr));
    if (skip == 0)
        skip = index_of(ptr, '\n', (int) (end_ptr - ptr) + 2);
    ptr += skip;
    return ptr;
}
bool game_load_campaign_file() {
    const char *filename = "campaign.txt";

    buffer buf(TMP_BUFFER_SIZE);
    int filesize = 0;
    filesize = io_read_file_into_buffer(filename, NOT_LOCALIZED, &buf, TMP_BUFFER_SIZE);
    if (filesize == 0) {
        log_error("Campaign file not found", 0, 0);
        return false;
    }

    // go through the file!
    buffer buf2(300);
    int num_lines = 0;
    int num_valid_lines = 0;
    int line_end;
    const uint8_t *haystack = buf.get_data();
    const uint8_t *ptr = &haystack[0];
    int action = -2;
    int data_line_idx = 0;
    do {
        line_end = index_of(ptr, '\n', filesize);
        int line_size = line_end;
        if (line_end == 0)
            line_size = filesize - (ptr - haystack);
        else
            line_size -= 2;
        const uint8_t *endl = ptr + line_size;
        int comment = index_of(ptr, ';', line_size);
        if (comment != 1 && line_size > 0) { // valid line
            if (index_of(ptr, '[', line_size)) { // header tag
                data_line_idx = 0;
                if (index_of_string(ptr, string_from_ascii("MISSION_NAMES"), line_size)) {
                    action = -1;
                } else {
                    data.num_campaigns++;
                    action++;
                }
            } else { // data tag
                if (action == -1) {
                    buf2.clear();
                    buf2.write_raw(ptr, line_size);
                    buf2.reset_offset();
                    buf2.read_raw(data.map_names[data_line_idx], line_size);
                    data.map_name_nums++;
                } else {
                    auto campaign = &data.campaigns[data.num_campaigns - 1];
                    // step data
                    if (index_of_string(ptr, string_from_ascii("mission"), line_size)) {
                        campaign->num_steps++;
                        auto step = &campaign->steps[campaign->num_steps - 1];
                        step->type = 0;
                        ptr = skip_non_digits(ptr);
                        ptr = get_value(ptr, endl, &step->mission.scenario_id);
                        ptr = get_value(ptr, endl, &step->mission.intro_MM);
                        ptr = get_value(ptr, endl, &step->mission.victory_text_id);
                        for (int i = 0; i < 5; ++i) {
                            if (index_of(ptr, '\n', line_size) > 2)
                                ptr = get_value(ptr, endl, &step->mission.path_ids[i]);
                            else
                                step->mission.path_ids[i] = -1;
                        }
                    } else if (index_of_string(ptr, string_from_ascii("choicescreen"), line_size)) {
                        if (campaign->num_steps == 0)
                            campaign->num_steps++;
                        auto step = &campaign->steps[campaign->num_steps - 1];
                        step->type = 1;
                        ptr = skip_non_digits(ptr);
                        ptr = get_value(ptr, endl, &step->choice.graphics_id);
                        ptr = get_value(ptr, endl, &step->choice.text_id);
                    } else if (index_of_string(ptr, string_from_ascii("choice"), line_size)) {
                        auto step = &campaign->steps[campaign->num_steps - 1]; // these MUST come after a VALID STEP.
                        auto branch = &step->choice.branches[step->choice.num_branches];
                        ptr = skip_non_digits(ptr);
                        ptr = get_value(ptr, endl, &branch->path_id);
                        ptr = get_value(ptr, endl, &branch->x);
                        ptr = get_value(ptr, endl, &branch->y);
                        ptr = get_value(ptr, endl, &branch->text_id);
                        step->choice.num_branches++;
                    }
                }
                data_line_idx++;
            }
            num_valid_lines++;
        }

        num_lines++;
        if (line_end)
            ptr = endl + 2;
    } while (line_end);
    // GOD, what a MESS!

    log_info("campaign.txt loaded", 0, 0);
    return true;
}