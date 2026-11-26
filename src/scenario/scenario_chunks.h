#pragma once

#include <cstddef>

class io_buffer;

struct scenario_mission_index_chunk {
    static constexpr const char* name = "scenario_mission_index";
    static void bind_data(io_buffer* iob);
};

struct scenario_info_chunk {
    static constexpr const char* name = "scenario_info";
    static void bind_data(io_buffer* iob);
};

struct scenario_carry_settings_chunk {
    static constexpr const char* name = "scenario_carry_settings";
    static void bind_data(io_buffer* iob);
};

struct scenario_is_custom_chunk {
    static constexpr const char* name = "scenario_is_custom";
    static void bind_data(io_buffer* iob);
};

struct scenario_map_name_chunk {
    static constexpr const char* name = "scenario_map_name";
    static void bind_data(io_buffer* iob);
};

struct city_scenario_chunk {
    static constexpr const char* name = "city_scenario";
    static constexpr int size = 12;
    static void bind_data(io_buffer* iob);
};
