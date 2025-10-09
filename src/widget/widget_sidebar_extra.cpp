#include "widget_sidebar_extra.h"

#include "city/city.h"
#include "game/game_events.h"
#include "city/city_population.h"
#include "city/ratings.h"
#include "core/string.h"
#include "game/game.h"
#include "graphics/graphics.h"
#include "graphics/elements/arrow_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/menu.h"
#include "graphics/elements/panel.h"
#include "window/autoconfig_window.h"
#include "graphics/image.h"
#include "graphics/text.h"
#include "game/game_config.h"
#include "io/gamefiles/lang.h"
#include "scenario/criteria.h"
#include "scenario/scenario.h"

#define EXTRA_INFO_LINE_SPACE 16
#define EXTRA_INFO_HEIGHT_GAME_SPEED 64
#define EXTRA_INFO_HEIGHT_UNEMPLOYMENT 48
#define EXTRA_INFO_HEIGHT_RATINGS 176
#define EXTRA_INFO_VERTICAL_PADDING 8

struct sidebar_window_extra : public autoconfig_window_t<sidebar_window_extra> {
    struct objective {
        int value = 0;
        int target = 0;

        void set_target(int v) { if (v > 0) { target = v; } }
    };

    vec2i offset;
    vec2i size;
    int is_collapsed;
    int info_to_display;
    int game_speed;
    int unemployment_percentage;
    int unemployment_amount;
    objective culture;
    objective prosperity;
    objective monument;
    objective kingdom;
    objective population;

    virtual int draw_background(UiFlags flags) override;
    virtual void draw_foreground(UiFlags flags) override;
    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual int get_tooltip_text() override { return 0; }
    virtual void init() override {}

    void set_objectives();
    bool update(int is_background);
    int calculate_height();

    void draw_objective(pcstr prefix, int text_group, int text_id, objective &obj);
    int calculate_displayable_info(int info_to_display, int available_height);

    virtual void archive_load(archive arch) override {
        widget::archive_load(arch);

        ui["dec_speed"].onclick([] { events::emit( event_change_gamespeed{ HOTKEY_DECREASE_GAME_SPEED }); });
        ui["inc_speed"].onclick([] { events::emit( event_change_gamespeed{ HOTKEY_INCREASE_GAME_SPEED }); });
    }
};

sidebar_window_extra g_sidebar_extra;

int sidebar_window_extra::calculate_displayable_info(int info_to_display, int available_height) {
    if (is_collapsed || !game_features::gameui_sidebar_info
        || info_to_display == SIDEBAR_EXTRA_DISPLAY_NONE)
        return SIDEBAR_EXTRA_DISPLAY_NONE;

    int result = SIDEBAR_EXTRA_DISPLAY_NONE;
    if (available_height >= EXTRA_INFO_HEIGHT_GAME_SPEED) {
        if (info_to_display & SIDEBAR_EXTRA_DISPLAY_GAME_SPEED) {
            available_height -= EXTRA_INFO_HEIGHT_GAME_SPEED;
            result |= SIDEBAR_EXTRA_DISPLAY_GAME_SPEED;
        }
    } else {
        return result;
    }

    if (available_height >= EXTRA_INFO_HEIGHT_UNEMPLOYMENT) {
        if (info_to_display & SIDEBAR_EXTRA_DISPLAY_UNEMPLOYMENT) {
            available_height -= EXTRA_INFO_HEIGHT_UNEMPLOYMENT;
            result |= SIDEBAR_EXTRA_DISPLAY_UNEMPLOYMENT;
        }
    } else {
        return result;
    }

    if (available_height >= EXTRA_INFO_HEIGHT_RATINGS) {
        if (info_to_display & SIDEBAR_EXTRA_DISPLAY_RATINGS) {
            available_height -= EXTRA_INFO_HEIGHT_RATINGS;
            result |= SIDEBAR_EXTRA_DISPLAY_RATINGS;
        }
    }
    return result;
}

int sidebar_window_extra::calculate_height() {
    if (is_collapsed) {
        return 0;
    }

    if (info_to_display == SIDEBAR_EXTRA_DISPLAY_NONE) {
        return 0;
    }

    int height = 0;
    height += (info_to_display & SIDEBAR_EXTRA_DISPLAY_GAME_SPEED) ? EXTRA_INFO_HEIGHT_GAME_SPEED : 0;
    height += (info_to_display & SIDEBAR_EXTRA_DISPLAY_UNEMPLOYMENT) ? EXTRA_INFO_HEIGHT_UNEMPLOYMENT : 0;
    height += (info_to_display & SIDEBAR_EXTRA_DISPLAY_RATINGS) ? EXTRA_INFO_HEIGHT_RATINGS : 0;

    return height;
}

void sidebar_window_extra::set_objectives() {
    if (scenario_is_open_play())
        return;

    culture.set_target(winning_culture());
    prosperity.set_target(winning_prosperity());
    monument.set_target(winning_monuments());
    kingdom.set_target(winning_kingdom());
    population.set_target(winning_population());
}

bool update_extra_info_value(int value, int& field) {
    int old_v = field;
    field = value;
    return (old_v == value);
}

bool sidebar_window_extra::update(int is_background) {
    bool changed = false;
    if (info_to_display & SIDEBAR_EXTRA_DISPLAY_GAME_SPEED)
        changed |= update_extra_info_value(game.game_speed, game_speed);

    if (info_to_display & SIDEBAR_EXTRA_DISPLAY_UNEMPLOYMENT) {
        changed |= update_extra_info_value(g_city.labor.unemployment_percentage, unemployment_percentage);
        changed |= update_extra_info_value(g_city.labor.workers_unemployed - g_city.labor.workers_needed, unemployment_amount);
    }
    if (info_to_display & SIDEBAR_EXTRA_DISPLAY_RATINGS) {
        if (is_background)
            set_objectives();

        changed |= update_extra_info_value(g_city.ratings.culture, culture.value);
        changed |= update_extra_info_value(g_city.ratings.prosperity, prosperity.value);
        changed |= update_extra_info_value(g_city.ratings.monument, monument.value);
        changed |= update_extra_info_value(g_city.kingdome.rating, kingdom.value);
        changed |= update_extra_info_value(g_city.population.current, population.value);
    }
    return changed;
}

void sidebar_window_extra::draw_objective(pcstr prefix, int text_group, int text_id, objective &obj) {
    auto id = [prefix] (pcstr key) { return bstring32(prefix, "_", key); };

    ui[id("header")] = ui::str(text_group, text_id);

    ui[id("current")].font((obj.value >= obj.target) ? FONT_NORMAL_BLACK_ON_DARK : FONT_NORMAL_YELLOW);
    ui[id("current")].text_var("%u (%u)", obj.value, obj.target);
}

int sidebar_window_extra::draw_background(UiFlags flags) {
    autoconfig_window::draw_background(flags);

    this->size.y = calculate_height();

    int available_height = screen_height() - offset.y - size.y;
    this->info_to_display = calculate_displayable_info(info_to_display, available_height);

    if (info_to_display != SIDEBAR_EXTRA_DISPLAY_NONE) {
        update(true);
    }

    const bool show_buttons = (info_to_display & SIDEBAR_EXTRA_DISPLAY_GAME_SPEED);
    ui["dec_speed"].enabled = show_buttons;
    ui["inc_speed"].enabled = show_buttons;

    const bool show_speed = (info_to_display & SIDEBAR_EXTRA_DISPLAY_GAME_SPEED);
    ui["speed_header"].enabled = show_speed;
    ui["speed_current"].enabled = show_speed;

    const bool show_emp = (info_to_display & SIDEBAR_EXTRA_DISPLAY_UNEMPLOYMENT);
    ui["unemp_header"].enabled = show_emp;
    ui["unemp_current"].enabled = show_emp;
    return size.y;
}

int sidebar_extra_draw(vec2i offset) {
    g_sidebar_extra.is_collapsed = city_view_is_sidebar_collapsed();
    g_sidebar_extra.info_to_display = SIDEBAR_EXTRA_DISPLAY_ALL;

    g_sidebar_extra.pos = offset;
    g_sidebar_extra.draw_background(0);
    g_sidebar_extra.draw_foreground(0);

    return g_sidebar_extra.calculate_height();
}

void sidebar_window_extra::draw_foreground(UiFlags flags) {
    if (is_collapsed) {
        return;
    }

    ui.begin_widget(pos);
    ui.draw();

    ui["speed_current"].text_var("%u%%", game_speed);
    ui["unemp_current"].text_var("%u%% (%d)", unemployment_percentage, unemployment_amount);

    draw_objective("population", 53, 6, population);
    draw_objective("culture", 53, 1, culture);
    draw_objective("prosperity", 53, 2, prosperity);
    draw_objective("monument", 53, 3, monument);
    draw_objective("kingdom", 53, 4, kingdom);
    
    ui.end_widget();
}
