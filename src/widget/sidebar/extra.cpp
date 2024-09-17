#include "extra.h"

#include "city/city.h"
#include "city/population.h"
#include "city/ratings.h"
#include "core/game_environment.h"
#include "core/string.h"
#include "game/settings.h"
#include "graphics/graphics.h"
#include "graphics/elements/arrow_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/menu.h"
#include "graphics/elements/panel.h"
#include "graphics/image.h"
#include "graphics/text.h"
#include "config/config.h"
#include "io/gamefiles/lang.h"
#include "scenario/criteria.h"
#include "scenario/scenario.h"

#define EXTRA_INFO_LINE_SPACE 16
#define EXTRA_INFO_HEIGHT_GAME_SPEED 64
#define EXTRA_INFO_HEIGHT_UNEMPLOYMENT 48
#define EXTRA_INFO_HEIGHT_RATINGS 176
#define EXTRA_INFO_VERTICAL_PADDING 8

static void button_game_speed(int is_down, int param2);

static arrow_button arrow_buttons_speed[] = {
  {11, 30, 17, 24, button_game_speed, 1, 0},
  {35, 30, 15, 24, button_game_speed, 0, 0},
};

struct extra_objective_t {
    int value;
    int target;
};

struct extra_data_t {
    int x_offset;
    int y_offset;
    int width;
    int height;
    int is_collapsed;
    int info_to_display;
    int game_speed;
    int unemployment_percentage;
    int unemployment_amount;
    extra_objective_t culture;
    extra_objective_t prosperity;
    extra_objective_t monument;
    extra_objective_t kingdom;
    extra_objective_t population;
};

extra_data_t g_extra_data;

static int calculate_displayable_info(int info_to_display, int available_height) {
    if (g_extra_data.is_collapsed || !config_get(CONFIG_UI_SIDEBAR_INFO)
        || info_to_display == SIDEBAR_EXTRA_DISPLAY_NONE)
        return SIDEBAR_EXTRA_DISPLAY_NONE;

    int result = SIDEBAR_EXTRA_DISPLAY_NONE;
    if (available_height >= EXTRA_INFO_HEIGHT_GAME_SPEED) {
        if (info_to_display & SIDEBAR_EXTRA_DISPLAY_GAME_SPEED) {
            available_height -= EXTRA_INFO_HEIGHT_GAME_SPEED;
            result |= SIDEBAR_EXTRA_DISPLAY_GAME_SPEED;
        }
    } else
        return result;
    if (available_height >= EXTRA_INFO_HEIGHT_UNEMPLOYMENT) {
        if (info_to_display & SIDEBAR_EXTRA_DISPLAY_UNEMPLOYMENT) {
            available_height -= EXTRA_INFO_HEIGHT_UNEMPLOYMENT;
            result |= SIDEBAR_EXTRA_DISPLAY_UNEMPLOYMENT;
        }
    } else
        return result;
    if (available_height >= EXTRA_INFO_HEIGHT_RATINGS) {
        if (info_to_display & SIDEBAR_EXTRA_DISPLAY_RATINGS) {
            available_height -= EXTRA_INFO_HEIGHT_RATINGS;
            result |= SIDEBAR_EXTRA_DISPLAY_RATINGS;
        }
    }
    return result;
}
static int calculate_extra_info_height(void) {
    if (g_extra_data.info_to_display == SIDEBAR_EXTRA_DISPLAY_NONE)
        return 0;

    int height = 0;
    if (g_extra_data.info_to_display & SIDEBAR_EXTRA_DISPLAY_GAME_SPEED)
        height += EXTRA_INFO_HEIGHT_GAME_SPEED;

    if (g_extra_data.info_to_display & SIDEBAR_EXTRA_DISPLAY_UNEMPLOYMENT)
        height += EXTRA_INFO_HEIGHT_UNEMPLOYMENT;

    if (g_extra_data.info_to_display & SIDEBAR_EXTRA_DISPLAY_RATINGS)
        height += EXTRA_INFO_HEIGHT_RATINGS;

    return height;
}

static void set_extra_info_objectives(void) {
    g_extra_data.culture.target = 0;
    g_extra_data.prosperity.target = 0;
    g_extra_data.monument.target = 0;
    g_extra_data.kingdom.target = 0;
    g_extra_data.population.target = 0;

    if (scenario_is_open_play())
        return;
    if (winning_culture())
        g_extra_data.culture.target = winning_culture();

    if (winning_prosperity())
        g_extra_data.prosperity.target = winning_prosperity();

    if (winning_monuments())
        g_extra_data.monument.target = winning_monuments();

    if (winning_kingdom())
        g_extra_data.kingdom.target = winning_kingdom();

    if (winning_population())
        g_extra_data.population.target = winning_population();
}
static int update_extra_info_value(int value, int* field) {
    if (value == *field)
        return 0;
    else {
        *field = value;
        return 1;
    }
}
static int update_extra_info(int is_background) {
    int changed = 0;
    if (g_extra_data.info_to_display & SIDEBAR_EXTRA_DISPLAY_GAME_SPEED)
        changed |= update_extra_info_value(g_settings.game_speed, &g_extra_data.game_speed);

    if (g_extra_data.info_to_display & SIDEBAR_EXTRA_DISPLAY_UNEMPLOYMENT) {
        changed |= update_extra_info_value(g_city.labor.unemployment_percentage, &g_extra_data.unemployment_percentage);
        changed |= update_extra_info_value(g_city.labor.workers_unemployed - g_city.labor.workers_needed, &g_extra_data.unemployment_amount);
    }
    if (g_extra_data.info_to_display & SIDEBAR_EXTRA_DISPLAY_RATINGS) {
        if (is_background)
            set_extra_info_objectives();

        changed |= update_extra_info_value(g_city.ratings.culture, &g_extra_data.culture.value);
        changed |= update_extra_info_value(g_city.ratings.prosperity, &g_extra_data.prosperity.value);
        changed |= update_extra_info_value(g_city.ratings.monument, &g_extra_data.monument.value);
        changed |= update_extra_info_value(g_city.ratings.kingdom, &g_extra_data.kingdom.value);
        changed |= update_extra_info_value(city_population(), &g_extra_data.population.value);
    }
    return changed;
}

static int draw_extra_info_objective(int x_offset, int y_offset, int text_group, int text_id, extra_objective_t* obj, int cut_off_at_parenthesis) {
    if (cut_off_at_parenthesis) {
        // Exception for Chinese: the string for "population" includes the hotkey " (6)"
        // To fix that: cut the string off at the '('
        // Also: Pharaoh's string contains ":" at the end (same fix)
        uint8_t tmp[100];
        string_copy(lang_get_string(text_group, text_id), tmp, 100);
        for (int i = 0; i < 100 && tmp[i]; i++) {
            if (tmp[i] == '(' || tmp[i] == ':') {
                tmp[i] = 0;
                break;
            }
        }
        text_draw(tmp, x_offset + 11, y_offset, FONT_NORMAL_WHITE_ON_DARK, 0);
    } else
        lang_text_draw(text_group, text_id, x_offset + 11, y_offset, FONT_NORMAL_WHITE_ON_DARK);
    e_font font = obj->value >= obj->target ? FONT_NORMAL_BLACK_ON_DARK : FONT_NORMAL_YELLOW;
    int width = text_draw_number(obj->value, '@', "", x_offset + 11, y_offset + EXTRA_INFO_LINE_SPACE, font);
    text_draw_number(obj->target, '(', ")", x_offset + 11 + width, y_offset + EXTRA_INFO_LINE_SPACE, font);
    return EXTRA_INFO_LINE_SPACE * 2;
}
static void draw_extra_info_panel(void) {
    auto &data = g_extra_data;
    graphics_draw_vertical_line(vec2i{data.x_offset, data.y_offset}, data.y_offset + data.height, COLOR_WHITE);
    graphics_draw_vertical_line(vec2i{data.x_offset + data.width - 1, data.y_offset}, data.y_offset + data.height, COLOR_SIDEBAR);
    inner_panel_draw(data.x_offset + 1, data.y_offset, data.width / 16, data.height / 16);

    int y_current_line = data.y_offset;

    if (data.info_to_display & SIDEBAR_EXTRA_DISPLAY_GAME_SPEED) {
        y_current_line += EXTRA_INFO_VERTICAL_PADDING * 2;

        lang_text_draw(45, 2, data.x_offset + 11, y_current_line, FONT_NORMAL_WHITE_ON_DARK);
        y_current_line += EXTRA_INFO_LINE_SPACE + EXTRA_INFO_VERTICAL_PADDING;

        text_draw_percentage(data.game_speed, data.x_offset + 60, y_current_line, FONT_NORMAL_BLACK_ON_DARK);
        arrow_buttons_draw({data.x_offset, data.y_offset}, arrow_buttons_speed, 2);

        y_current_line += EXTRA_INFO_VERTICAL_PADDING * 2;
    }

    if (data.info_to_display & SIDEBAR_EXTRA_DISPLAY_UNEMPLOYMENT) {
        y_current_line += EXTRA_INFO_VERTICAL_PADDING;

        //if (GAME_ENV == ENGINE_ENV_C3)
        //    lang_text_draw(68, 148, data.x_offset + 11, y_current_line, FONT_NORMAL_WHITE_ON_DARK);
        //else
            lang_text_draw(68, 135, data.x_offset + 11, y_current_line, FONT_NORMAL_WHITE_ON_DARK);
        y_current_line += EXTRA_INFO_LINE_SPACE;

        int text_width = text_draw_percentage(data.unemployment_percentage, data.x_offset + 11, y_current_line, FONT_NORMAL_BLACK_ON_DARK);
        text_draw_number(data.unemployment_amount, '(', ")", data.x_offset + 11 + text_width, y_current_line, FONT_NORMAL_BLACK_ON_DARK);

        y_current_line += EXTRA_INFO_VERTICAL_PADDING * 2;
    }

    if (data.info_to_display & SIDEBAR_EXTRA_DISPLAY_RATINGS) {
        y_current_line += EXTRA_INFO_VERTICAL_PADDING;
        y_current_line += draw_extra_info_objective(data.x_offset, y_current_line, 53, 6, &data.population, 1);
        //            y_current_line += draw_extra_info_objective(data.x_offset, y_current_line, 44, 56,
        //            &data.population, 1);
        y_current_line += draw_extra_info_objective(data.x_offset, y_current_line, 53, 1, &data.culture, 0);
        y_current_line += draw_extra_info_objective(data.x_offset, y_current_line, 53, 2, &data.prosperity, 0);
        y_current_line += draw_extra_info_objective(data.x_offset, y_current_line, 53, 3, &data.monument, 0);
        y_current_line += draw_extra_info_objective(data.x_offset, y_current_line, 53, 4, &data.kingdom, 0);
    }
    // todo: extra goal / required households
}
int sidebar_extra_draw_background(int x_offset,
                                  int y_offset,
                                  int width,
                                  int available_height,
                                  int is_collapsed,
                                  int info_to_display) {
    auto& data = g_extra_data;
    //    if (GAME_ENV == ENGINE_ENV_PHARAOH)
    //        x_offset -= 24;
    data.is_collapsed = is_collapsed;
    data.x_offset = x_offset;
    data.y_offset = y_offset;
    data.width = width;
    data.info_to_display = calculate_displayable_info(info_to_display, available_height);
    data.height = calculate_extra_info_height();

    if (data.info_to_display != SIDEBAR_EXTRA_DISPLAY_NONE) {
        update_extra_info(1);
        draw_extra_info_panel();
    }
    return data.height;
}
void sidebar_extra_draw_foreground(void) {
    auto& data = g_extra_data;
    if (update_extra_info(0)) {
        draw_extra_info_panel(); // Updates displayed speed % after clicking the arrows
    } 
    
    if (data.info_to_display & SIDEBAR_EXTRA_DISPLAY_GAME_SPEED) {
        arrow_buttons_draw({ data.x_offset, data.y_offset }, arrow_buttons_speed, 2);
    }
}

int sidebar_extra_handle_mouse(const mouse* m) {
    auto& data = g_extra_data;
    if (!(data.info_to_display & SIDEBAR_EXTRA_DISPLAY_GAME_SPEED))
        return 0;

    return arrow_buttons_handle_mouse(m, {data.x_offset, data.y_offset}, arrow_buttons_speed, 2, 0);
}

static void button_game_speed(int is_down, int param2) {
    if (is_down)
        g_settings.decrease_game_speed();
    else {
        g_settings.increase_game_speed();
    }
}
