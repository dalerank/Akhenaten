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
        mission_step_t steps[50];
        int num_steps = 0;
    } campaigns[MAX_MISSION_CAMPAIGNS];
    int num_campaigns = 0;
} data;

bool matches_path_id(const mission_step_t *step, int path_id) {
    for (int i = 0; i < MAX_MISSION_STEP_BRANCHES; ++i) {
        if (step->path_ids[i] == path_id)
            return true; // ONLY match with the provided id. the default path id merger (0) is checked MANUALLY!
    }
    return false;
}
static mission_step_t *find_next_connected_path_step(const mission_step_t *step, int path_id) {
    auto next = step->next_in_list;
    while (next != nullptr) {
        if (matches_path_id(next, path_id))
            return next;
        // should we do this? why not...
        if (next->is_campaign_end && next->campaign_id > -1 && next->campaign_id < data.num_campaigns - 1)
            return &data.campaigns[next->campaign_id + 1].steps[0];
        next = next->next_in_list;
    }
    return nullptr;
}
static mission_step_t *find_next(const mission_step_t *step, int choice_index = 0) {
    if (!step->has_choice)
        return find_next_connected_path_step(step, 0);
    else {
        auto choice = step->branches[choice_index];
        return find_next_connected_path_step(step, choice.path_id);
    }
    return nullptr; // this should never happen?
}
static void find_in_campaigns(int scenario_id, int *campaign_id, int *step_index) {
    for (int c = 0; c < data.num_campaigns; ++c) {
        auto campaign = &data.campaigns[c];
        for (int i = 0; i < campaign->num_steps; ++i) {
            auto step = &campaign->steps[i];
            if (step->scenario_id == scenario_id) {
                *campaign_id = c;
                *step_index = i;
                return;
            }
        }
    }
    // no matching scenario found!
    *campaign_id = -1;
    *step_index = -1;
}
const uint8_t *game_mission_get_name(int scenario_id) {
    if (scenario_id >= data.map_name_nums || scenario_id > 299)
        return data.map_names[0];
    return data.map_names[scenario_id];
}
const mission_step_t *game_campaign_get_step_data(int campaign_id, int step_index) {
    if (campaign_id < -1 || campaign_id >= data.num_campaigns)
        return nullptr;
    auto campaign = &data.campaigns[campaign_id];
    if (step_index < -1 || step_index > campaign->num_steps)
        return nullptr;
    return &data.campaigns[campaign_id].steps[step_index];
}
const mission_step_t *game_scenario_get_step_data(int scenario_id) {
    int campaign_id = -1;
    int step_index = -1;
    find_in_campaigns(scenario_id, &campaign_id, &step_index);
    return game_campaign_get_step_data(campaign_id, step_index);
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
        if (comment != 1 && line_size > 0) { // valid line!
            if (index_of(ptr, '[', line_size)) { // braced tag
                data_line_idx = 0;
                if (index_of_string(ptr, string_from_ascii("MISSION_NAMES"), line_size)) {
                    action = -1;
                } else {
//                    if (action > -1) { // END of the previous campaign
//                        auto campaign = &data.campaigns[data.num_campaigns - 1];
//                        auto step = &campaign->steps[campaign->num_steps - 1];
//                        step->is_campaign_end = true;
//                    }
                    data.num_campaigns++;
                    action++;
                }
            } else { // data line
                if (action == -1) { // map names
                    buf2.clear();
                    buf2.write_raw(ptr, line_size);
                    buf2.reset_offset();
                    buf2.read_raw(data.map_names[data_line_idx], line_size);
                    data.map_name_nums++;
                } else { // mission data
                    auto campaign = &data.campaigns[data.num_campaigns - 1];
                    if (index_of_string(ptr, string_from_ascii("mission"), line_size)) { // mission step data
                        campaign->num_steps++;
                        auto step = &campaign->steps[campaign->num_steps - 1];
//                        step->type = CAMPAIGN_STEP_MISSION;
                        ptr = skip_non_digits(ptr);
                        ptr = get_value(ptr, endl, &step->scenario_id);
                        ptr = get_value(ptr, endl, &step->intro_MM);
                        ptr = get_value(ptr, endl, &step->victory_text_id);
                        for (int i = 0; i < MAX_MISSION_STEP_BRANCHES; ++i) {
                            if (index_of(ptr, '\n', line_size) > 2)
                                ptr = get_value(ptr, endl, &step->path_ids[i]);
                            else
                                step->path_ids[i] = -1; // just to be safe...
                        }
                        step->map_name = (const uint8_t*)data.map_names[step->scenario_id];
                        step->campaign_id = data.num_campaigns - 1;
                        // linked list pointers
                        if (campaign->num_steps > 1) { // previous one is the mission immediately preceding this one
                            step->previous_in_list = &campaign->steps[campaign->num_steps - 2];
                            step->previous_in_list->next_in_list = step;
                        } else if (data.num_campaigns > 1) { // previous one is the last one in PREVIOUS CAMPAIGN
                            auto prev_campaign = &data.campaigns[data.num_campaigns - 2];
                            step->previous_in_list = &prev_campaign->steps[prev_campaign->num_steps - 1];
                            step->previous_in_list->next_in_list = step;
                        }
                    } else if (index_of_string(ptr, string_from_ascii("choicescreen"), line_size)) { // choice screen data
                        if (campaign->num_steps == 0)
                            campaign->num_steps++;
                        auto step = &campaign->steps[campaign->num_steps - 1];
                        step->has_choice = true;
                        ptr = skip_non_digits(ptr);
                        ptr = get_value(ptr, endl, &step->graphics_id);
                        ptr = get_value(ptr, endl, &step->text_id);
                    } else if (index_of_string(ptr, string_from_ascii("choice"), line_size)) { // choice branch data
                        auto step = &campaign->steps[campaign->num_steps - 1]; // these MUST come after a valid CHOICESCREEN tag.
                        auto branch = &step->branches[step->num_branches];
                        ptr = skip_non_digits(ptr);
                        ptr = get_value(ptr, endl, &branch->path_id);
                        ptr = get_value(ptr, endl, &branch->x);
                        ptr = get_value(ptr, endl, &branch->y);
                        ptr = get_value(ptr, endl, &branch->text_id);
                        step->num_branches++;
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

    // finalize loading, clean up things, generate advanced pointers/helper members etc.
    for (int c = 0; c < data.num_campaigns; ++c) {
        auto campaign = &data.campaigns[c];
        auto last_step = &campaign->steps[campaign->num_steps - 1];
        last_step->is_campaign_end = true;
        for (int i = 0; i < campaign->num_steps; ++i) {
            auto step = &campaign->steps[i];
            for (int j = 0; j < step->num_branches; ++j) {
                auto branch = &step->branches[j];
                branch->mission = find_next_connected_path_step(step, branch->path_id);
            }
        }
    }

    log_info("Campaign mission data loaded", 0, 0);
    return true;
}