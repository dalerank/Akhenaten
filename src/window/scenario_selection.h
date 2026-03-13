#pragma once

enum e_map_selection_dialog_type {
    MAP_SELECTION_CCK_LEGACY,
    MAP_SELECTION_CUSTOM,
    MAP_SELECTION_CAMPAIGN,
    MAP_SELECTION_CAMPAIGN_SINGLE_LIST,
    MAP_SELECTION_CAMPAIGN_UNUSED_BACKGROUND
};

void window_scenario_selection_show(int dialog_type);
