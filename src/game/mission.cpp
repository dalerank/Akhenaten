#include "mission.h"

#include "core/log.h"
#include "core/buffer.h"
#include "core/string.h"
#include "content/vfs.h"
#include "io/io.h"
#include "game/player.h"
#include "scenario/scenario.h"

struct mission_data_t {
    uint8_t map_names[300][300];
    int map_name_nums = 0;

    struct {
        mission_step_t steps[50];
        int num_steps = 0;
    } campaigns[MAX_MISSION_CAMPAIGNS];
    int num_campaigns = 0;
};

mission_data_t g_mission_data;

bool matches_path_id(const mission_step_t* step, int path_id) {
    for (int i = 0; i < MAX_MISSION_CHOICE_BRANCHES; ++i) {
        if (step->path_ids[i] == path_id)
            return true; // ONLY match with the provided id. the default path id merger (0) is checked MANUALLY!
    }
    return false;
}
static mission_step_t* find_next_connected_path_step(const mission_step_t* step, int path_id) {
    auto next = step->next_in_list;
    while (next != nullptr) {
        if (matches_path_id(next, 0)) // first, check for default path id merging (0)
            return next;
        if (matches_path_id(next, path_id))
            return next;
        // should we do this? why not...
        if (next->is_campaign_end && next->campaign_id > -1 && next->campaign_id < g_mission_data.num_campaigns - 1)
            return &g_mission_data.campaigns[next->campaign_id + 1].steps[0];
        next = next->next_in_list;
    }
    return nullptr;
}
static mission_step_t* find_next(const mission_step_t* step, int choice_index = 0) {
    if (!step->has_choice) {
        return find_next_connected_path_step(step, 0);
    } else {
        // auto choice = step->branches[choice_index];
        //return find_next_connected_path_step(step, choice.path_id);
        return find_next_connected_path_step(step, 0);
    }
    return nullptr; // this should never happen?
}

struct campaign_mission_id {
    int campaign_id = -1;
    int step_index = -1;
};

campaign_mission_id find_in_campaigns(int scenario_id) {
    for (int c = 0; c < g_mission_data.num_campaigns; ++c) {
        auto campaign = &g_mission_data.campaigns[c];
        for (int i = 0; i < campaign->num_steps; ++i) {
            auto step = &campaign->steps[i];
            if (step->scenario_id == scenario_id) {
                return { c, i };
            }
        }
    }
    // no matching scenario found!
    return { -1, -1 };
}

const uint8_t* game_mission_get_name(int scenario_id) {
    if (scenario_id >= g_mission_data.map_name_nums || scenario_id > 299)
        return g_mission_data.map_names[0];
    return g_mission_data.map_names[scenario_id];
}
const mission_step_t* get_campaign_mission_step_data(int campaign_id, int step_index) {
    if (campaign_id < -1 || campaign_id >= g_mission_data.num_campaigns)
        return nullptr;
    auto campaign = &g_mission_data.campaigns[campaign_id];
    if (step_index < -1 || step_index > campaign->num_steps)
        return nullptr;
    return &g_mission_data.campaigns[campaign_id].steps[step_index];
}

const mission_step_t* get_scenario_step_data(int scenario_id) {
    campaign_mission_id m = find_in_campaigns(scenario_id);
    return get_campaign_mission_step_data(m.campaign_id, m.step_index);
}

int get_scenario_mission_rank(int scenario_id) {
    const mission_step_t *mission = get_scenario_step_data(scenario_id);
    return mission->mission_rank;
}

int get_scenario_campaign_id(int scenario_id) {
    if (scenario_id < SCENARIO_NULL || scenario_id >= SCENARIO_MAX)
        return CAMPAIGN_NULL;
    auto step = get_scenario_step_data(scenario_id);
    if (step != nullptr)
        return step->campaign_id;
    return CAMPAIGN_NULL;
}
int get_first_mission_in_campaign(int campaign_id) {
    if (campaign_id < CAMPAIGN_PHARAOH_PREDYNASTIC || campaign_id >= CAMPAIGN_MAX)
        return SCENARIO_NULL;
    auto campaign = &g_mission_data.campaigns[campaign_id];
    auto step = &campaign->steps[0];
    while (step->scenario_id == SCENARIO_NULL)
        step = step->next_in_list;
    return step->scenario_id;
}

int get_last_mission_in_campaign(int campaign_id) {
    if (campaign_id < CAMPAIGN_PHARAOH_PREDYNASTIC || campaign_id >= CAMPAIGN_MAX)
        return SCENARIO_NULL;
    auto campaign = &g_mission_data.campaigns[campaign_id];
    return campaign->steps[campaign->num_steps - 1].scenario_id;
}

bool game_mission_has_choice(int scenario_id) {
    mission_id_t missionid(scenario_id);
    mission_choice_t choices = load_mission_choice(missionid);
    return !choices.choice.empty();
}

bool game_campaign_unlocked(int campaign_id) {
    return game_scenario_unlocked(get_first_mission_in_campaign(campaign_id));
    //    switch (campaign_id) {
    //        // pharaoh
    //        case CAMPAIGN_PHARAOH_ARCHAIC:
    //            return game_scenario_unlocked(SCENARIO_NUBT);
    //        case CAMPAIGN_PHARAOH_PREDYNASTIC:
    //            return game_scenario_unlocked(SCENARIO_NEKHEN);
    //        case CAMPAIGN_PHARAOH_OLD_KINGDOM:
    //            return game_scenario_unlocked(SCENARIO_SELIMA_OASIS);
    //        case CAMPAIGN_PHARAOH_MIDDLE_KINGDOM:
    //            return game_scenario_unlocked(SCENARIO_THINIS_2);
    //        case CAMPAIGN_PHARAOH_NEW_KINGDOM:
    //            return game_scenario_unlocked(SCENARIO_KHMUN);
    //            // cleopatra
    //        case CAMPAIGN_CLEOPATRA_VALLEY_OF_THE_KINGS:
    //            return game_scenario_unlocked(SCENARIO_VALLEY_THUTMOSE);
    //        case CAMPAIGN_CLEOPATRA_RAMSES_II:
    //            return game_scenario_unlocked(SCENARIO_SUMUR);
    //        case CAMPAIGN_CLEOPATRA_ANCIENT_CONQUERORS:
    //            return game_scenario_unlocked(SCENARIO_PI_YER);
    //        case CAMPAIGN_CLEOPATRA_CLEOPATRAS_CAPITAL:
    //            return game_scenario_unlocked(SCENARIO_ALEXANDRIA_1);
    //    }
}
bool is_step_unlocked(const mission_step_t* step) {
    if (step->requirements[0] == nullptr)
        return true;
    // if otherwise specified, this scenario requires specific ones to unlock;
    // any one of them in the req. group will suffice to unlock the scenario.
    for (int i = 0; i < MAX_MISSION_CHOICE_BRANCHES; ++i) {
        auto req = step->requirements[i];
        if (req != nullptr) {
            if (req->scenario_id == SCENARIO_NULL) { // a dangling choice screen: traverse the tree upwards
                if (is_step_unlocked(req))
                    return true;
            } else { // found a valid mission field
                if (game_scenario_beaten(req->scenario_id))
                    return true;
            }
        }
    }
    return false;
}
bool game_scenario_unlocked(int scenario_id) {
    if (scenario_id < 0 || scenario_id >= SCENARIO_MAX) // invalid mission index
        return false;
    switch (scenario_id) {
    case SCENARIO_NUBT:
    case SCENARIO_VALLEY_THUTMOSE:
        return true; // first mission is always unlocked
    }
    auto step = get_scenario_step_data(scenario_id);
    return is_step_unlocked(step);
}
bool game_scenario_beaten(int scenario_id) {
    if (scenario_id < 0 || scenario_id >= SCENARIO_MAX) // invalid mission index
        return false;
    auto record = player_get_scenario_record(scenario_id);
    return record->nonempty;
}

#define TMP_BUFFER_SIZE 10000
static const uint8_t* CAMPAIGN_FILE_BEGIN = (const uint8_t * )string_from_ascii("\n[MISSION_NAMES]\n");
static const uint8_t* skip_non_digits(const uint8_t* str) {
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

static const uint8_t* get_value(const uint8_t* ptr, const uint8_t* end_ptr, int* value) {
    ptr = skip_non_digits(ptr);
    *value = string_to_int(ptr);
    int skip = index_of(ptr, ',', (int)(end_ptr - ptr));
    if (skip == 0)
        skip = index_of(ptr, '\n', (int)(end_ptr - ptr) + 2) - 1;
    ptr += skip;
    return ptr;
}

bool game_load_campaign_file() {
    const char* filename = "campaign.txt";

    buffer buf(TMP_BUFFER_SIZE);
    int filesize = 0;
    filesize = io_read_file_into_buffer(filename, NOT_LOCALIZED, &buf, TMP_BUFFER_SIZE);
    if (filesize == 0) {
        logs::error("Campaign file not found");
        return false;
    }

    // go through the file!
    buffer buf2(300);
    int num_lines = 0;
    int num_valid_lines = 0;
    int line_end;
    const uint8_t* haystack = buf.get_data();
    const uint8_t* ptr = &haystack[0];
    int action = -2;
    int data_line_idx = 0;
    do {
        line_end = index_of(ptr, '\n', filesize);
        int line_size = line_end;
        if (line_end == 0)
            line_size = filesize - (ptr - haystack);
        else
            line_size -= 2;
        const uint8_t* endl = ptr + line_size;
        int comment = index_of(ptr, ';', line_size);
        if (comment != 1 && line_size > 0) {     // valid line!
            if (index_of(ptr, '[', line_size)) { // braced tag
                data_line_idx = 0;
                if (index_of_string((pcstr)ptr, string_from_ascii("MISSION_NAMES"), line_size)) { // scenario names...
                    action = -1;
                } else { // start of a campaign block
                    g_mission_data.num_campaigns++;
                    action++;
                }
            } else {                // data line
                if (action == -1) { // map names
                    buf2.clear();
                    buf2.write_raw(ptr, line_size);
                    buf2.reset_offset();
                    buf2.read_raw(g_mission_data.map_names[data_line_idx], line_size);
                    g_mission_data.map_name_nums++;
                } else { // mission data
                    auto campaign = &g_mission_data.campaigns[g_mission_data.num_campaigns - 1];
                    if (index_of_string((pcstr)ptr, string_from_ascii("mission"), line_size)) { // mission step data
                        campaign->num_steps++;
                        auto step = &campaign->steps[campaign->num_steps - 1];
                        ptr = skip_non_digits(ptr);
                        ptr = get_value(ptr, endl, &step->scenario_id);
                        ptr = get_value(ptr, endl, &step->intro_MM);
                        ptr = get_value(ptr, endl, &step->victory_text_id);
                        for (int i = 0; i < MAX_MISSION_CHOICE_BRANCHES; ++i) {
                            // TODO warning: passing NULL to non-pointer argument
                            bool end_of_line = (index_of(ptr, '\n', line_size) == 1
                                                || index_of(ptr, '\0', line_size) == 1);
                            if (!end_of_line)
                                ptr = get_value(ptr, endl, &step->path_ids[i]);
                            else
                                step->path_ids[i] = -1; // just to be safe...
                        }
                        step->map_name = (const uint8_t*)g_mission_data.map_names[step->scenario_id];
                        step->campaign_id = g_mission_data.num_campaigns - 1;
                        // first mission rank is always 0
                        if (step->campaign_id == 0 && campaign->num_steps == 1)
                            step->mission_rank = 0;
                        // linked list pointers
                        if (campaign->num_steps > 1) { // previous one is the mission immediately preceding this one
                            step->previous_in_list = &campaign->steps[campaign->num_steps - 2];
                            step->previous_in_list->next_in_list = step;
                        } else if (g_mission_data.num_campaigns
                                   > 1) { // previous one is the last one in PREVIOUS CAMPAIGN
                            auto prev_campaign = &g_mission_data.campaigns[g_mission_data.num_campaigns - 2];
                            step->previous_in_list = &prev_campaign->steps[prev_campaign->num_steps - 1];
                            step->previous_in_list->next_in_list = step;
                        }
                    } else if (index_of_string((pcstr)ptr, string_from_ascii("choicescreen"), line_size)) { // choice screen data
                        if (campaign->num_steps == 0)
                            campaign->num_steps++;
                        auto step = &campaign->steps[campaign->num_steps - 1];
                        step->has_choice = true;
                        ptr = skip_non_digits(ptr);
                        ptr = get_value(ptr, endl, &step->graphics_id);
                        ptr = get_value(ptr, endl, &step->text_id);
                        if (step->scenario_id
                            == -1) { // a choice screen invoked automatically, with no previous scenario
                            step->path_ids[0] = 0;
                        }
                        if (step->scenario_id == -1
                            && g_mission_data.num_campaigns
                                 > 1) { // dangling choice screen at the start of a campaign!!
                            auto prev_campaign = &g_mission_data.campaigns[g_mission_data.num_campaigns - 2];
                            step->previous_in_list = &prev_campaign->steps[prev_campaign->num_steps - 1];
                            step->previous_in_list->next_in_list = step;
                        }
                    } else if (index_of_string((pcstr)ptr, string_from_ascii("choice"), line_size)) { // choice branch data
                        auto step = &campaign->steps[campaign->num_steps - 1]; // these MUST come after a valid CHOICESCREEN tag.
                        //auto branch = &step->branches[step->num_branches];
                        //ptr = skip_non_digits(ptr);
                        //ptr = get_value(ptr, endl, &branch->path_id);
                        //ptr = get_value(ptr, endl, &branch->x);
                        //ptr = get_value(ptr, endl, &branch->y);
                        //ptr = get_value(ptr, endl, &branch->text_id);
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
    // GOD, what a MESS!!

    // finalize loading, clean up things, generate advanced pointers/helper members etc.
    for (int c = 0; c < g_mission_data.num_campaigns; ++c) {
        auto campaign = &g_mission_data.campaigns[c];
        auto last_step = &campaign->steps[campaign->num_steps - 1];
        last_step->is_campaign_end = true;
        for (int i = 0; i < campaign->num_steps; ++i) {
            auto step = &campaign->steps[i];

            // give by default the merging path id (0) as a branch
            if (step->num_branches == 0) {
                step->num_branches = 1;
                //step->branches[0].path_id = step->path_ids[0];
            }

            // go through the branches (choices)...
            for (int j = 0; j < step->num_branches; ++j) {
                //auto branch = &step->branches[j];
                //
                //// set the branch pointer to the correct next mission (step) struct
                //branch->next_play = find_next_connected_path_step(step, branch->path_id);
                //
                //// fill in the back-pointing "requirements" pointers inside the next mission struct
                //if (branch->next_play != nullptr) {
                //    int first_free_slot = -1; // fill in the first empty space
                //    for (int k = 0; k < MAX_MISSION_CHOICE_BRANCHES; ++k) {
                //        if (branch->next_play->requirements[k] == nullptr && first_free_slot == -1) {
                //            first_free_slot = k;
                //            break;
                //        }
                //    }
                //    branch->next_play->requirements[first_free_slot] = step;
                //
                //    // increase the mission rank
                //    if (branch->next_play->mission_rank < step->mission_rank) {
                //        if (branch->next_play->scenario_id == -1)
                //            branch->next_play->mission_rank = step->mission_rank;
                //        else
                //            branch->next_play->mission_rank = step->mission_rank + 1;
                //    }
                //}
            }
        }
    }

    logs::info("Campaign mission data loaded");
    return true;
}

mission_choice_t load_mission_choice(const mission_id_t &missionid) {
    mission_choice_t mission_choice;
    g_config_arch.r(missionid, mission_choice);
    return mission_choice;
}