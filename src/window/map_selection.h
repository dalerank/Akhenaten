#ifndef WINDOW_CCK_SELECTION_H
#define WINDOW_CCK_SELECTION_H

typedef enum {
    MAP_SELECTION_CCK_LEGACY,
    MAP_SELECTION_CUSTOM,
    MAP_SELECTION_CAMPAIGN,
    MAP_SELECTION_CAMPAIGN_SINGLE_LIST,
    MAP_SELECTION_CAMPAIGN_UNUSED_BACKGROUND
} map_selection_dialog_type;

void window_map_selection_show(map_selection_dialog_type dialog_type);

#endif // WINDOW_CCK_SELECTION_H
