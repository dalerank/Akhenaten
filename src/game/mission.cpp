#include "mission.h"

#include "core/log.h"
#include "core/buffer.h"
#include "core/string.h"
#include "content/vfs.h"
#include "io/io.h"
#include "game/player.h"

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

struct campaign_mission_id {
    int campaign_id = -1;
    int step_index = -1;
};

static campaign_mission_id find_in_campaigns(int scenario_id) {
    for (int c = 0; c < g_mission_data.num_campaigns; ++c) {
        auto campaign = &g_mission_data.campaigns[c];
        for (int i = 0; i < campaign->num_steps; ++i) {
            auto step = &campaign->steps[i];
            if (step->scenario_id == scenario_id) {
                return { c, i };
            }
        }
    }
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

int get_scenario_campaign_id(int scenario_id) {
    if (scenario_id < SCENARIO_NULL || scenario_id >= SCENARIO_MAX) {
        return CAMPAIGN_NULL;
    }

    auto step = get_scenario_step_data(scenario_id);
    if (step != nullptr) {
        return step->campaign_id;
    }

    return CAMPAIGN_NULL;
}

int get_first_mission_in_campaign(int campaign_id) {
    if (campaign_id < CAMPAIGN_PHARAOH_PREDYNASTIC || campaign_id >= CAMPAIGN_MAX)
        return SCENARIO_NULL;

    auto campaign = &g_mission_data.campaigns[campaign_id];
    auto step = &campaign->steps[0];
    while (step->scenario_id == SCENARIO_NULL) {
        step = step->next_in_list;
    }

    return step->scenario_id;
}

bool game_scenario_beaten(int scenario_id) {
    if (scenario_id < 0 || scenario_id >= SCENARIO_MAX)
        return false;
    auto record = player_get_scenario_record(scenario_id);
    return record->nonempty;
}

#define TMP_BUFFER_SIZE 10000
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

// Legacy campaign.txt fields consumed but not used for runtime branching.
static void skip_choice_branch_fields(const uint8_t*& ptr, const uint8_t* endl) {
    int tmp = 0;
    ptr = skip_non_digits(ptr);
    ptr = get_value(ptr, endl, &tmp);
    ptr = get_value(ptr, endl, &tmp);
    ptr = get_value(ptr, endl, &tmp);
    ptr = get_value(ptr, endl, &tmp);
}

bool game_load_campaign_file() {
    const char* filename = "campaign.txt";

    buffer buf(TMP_BUFFER_SIZE);
    int filesize = io_read_file_into_buffer(filename, NOT_LOCALIZED, &buf, TMP_BUFFER_SIZE);
    if (filesize == 0) {
        logs::error("Campaign file not found");
        return false;
    }

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
        if (comment != 1 && line_size > 0) {
            if (index_of(ptr, '[', line_size)) {
                data_line_idx = 0;
                if (index_of_string((pcstr)ptr, string_from_ascii("MISSION_NAMES"), line_size)) {
                    action = -1;
                } else {
                    g_mission_data.num_campaigns++;
                    action++;
                }
            } else {
                if (action == -1) {
                    buf2.clear();
                    buf2.write_raw(ptr, line_size);
                    buf2.reset_offset();
                    buf2.read_raw(g_mission_data.map_names[data_line_idx], line_size);
                    g_mission_data.map_name_nums++;
                } else {
                    auto campaign = &g_mission_data.campaigns[g_mission_data.num_campaigns - 1];
                    if (index_of_string((pcstr)ptr, string_from_ascii("mission"), line_size)) {
                        campaign->num_steps++;
                        auto step = &campaign->steps[campaign->num_steps - 1];
                        ptr = skip_non_digits(ptr);
                        ptr = get_value(ptr, endl, &step->scenario_id);
                        ptr = get_value(ptr, endl, &step->intro_MM);
                        ptr = get_value(ptr, endl, &step->victory_text_id);
                        for (int i = 0; i < MAX_MISSION_CHOICE_BRANCHES; ++i) {
                            bool end_of_line = (index_of(ptr, '\n', line_size) == 1
                                                || index_of(ptr, '\0', line_size) == 1);
                            if (!end_of_line)
                                ptr = get_value(ptr, endl, &step->path_ids[i]);
                            else
                                step->path_ids[i] = -1;
                        }
                        step->map_name = (const uint8_t*)g_mission_data.map_names[step->scenario_id];
                        step->campaign_id = g_mission_data.num_campaigns - 1;
                        if (step->campaign_id == 0 && campaign->num_steps == 1)
                            step->mission_rank = 0;
                        if (campaign->num_steps > 1) {
                            step->previous_in_list = &campaign->steps[campaign->num_steps - 2];
                            step->previous_in_list->next_in_list = step;
                        } else if (g_mission_data.num_campaigns > 1) {
                            auto prev_campaign = &g_mission_data.campaigns[g_mission_data.num_campaigns - 2];
                            step->previous_in_list = &prev_campaign->steps[prev_campaign->num_steps - 1];
                            step->previous_in_list->next_in_list = step;
                        }
                    } else if (index_of_string((pcstr)ptr, string_from_ascii("choicescreen"), line_size)) {
                        // Legacy choice-screen row: keep parser in sync, no runtime effect.
                        if (campaign->num_steps == 0)
                            campaign->num_steps++;
                        auto step = &campaign->steps[campaign->num_steps - 1];
                        int tmp_graphics = 0;
                        int tmp_text = 0;
                        ptr = skip_non_digits(ptr);
                        ptr = get_value(ptr, endl, &tmp_graphics);
                        ptr = get_value(ptr, endl, &tmp_text);
                        if (step->scenario_id == -1)
                            step->path_ids[0] = 0;
                        if (step->scenario_id == -1 && g_mission_data.num_campaigns > 1) {
                            auto prev_campaign = &g_mission_data.campaigns[g_mission_data.num_campaigns - 2];
                            step->previous_in_list = &prev_campaign->steps[prev_campaign->num_steps - 1];
                            step->previous_in_list->next_in_list = step;
                        }
                    } else if (index_of_string((pcstr)ptr, string_from_ascii("choice"), line_size)) {
                        skip_choice_branch_fields(ptr, endl);
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

    for (int c = 0; c < g_mission_data.num_campaigns; ++c) {
        auto campaign = &g_mission_data.campaigns[c];
        if (campaign->num_steps > 0) {
            campaign->steps[campaign->num_steps - 1].is_campaign_end = true;
        }
    }

    logs::info("Campaign mission data loaded");
    return true;
}
