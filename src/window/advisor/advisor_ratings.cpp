#include "advisor_ratings.h"

#include "city/city.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/view/view.h"
#include "graphics/elements/ui.h"
#include "graphics/screen.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "config/config.h"
#include "scenario/criteria.h"
#include "scenario/scenario.h"
#include "game/game.h"

#include "js/js_game.h"

ui::advisor_ratings_window g_advisor_rating_window;
constexpr pcstr rating_buttons[] = {"culture", "prosperity", "monument", "kingdom"};

void ui::advisor_ratings_window::draw_rating_column(int id, int value, int open_play, int goal) {
    int enabled = !open_play && goal;
    int has_reached = !enabled || value >= goal;

    pcstr idstr = rating_buttons[id];
    bstring64 baseid("base_", idstr);

    vec2i pos = ui[baseid].pos;

    int value_to_draw = value * 0.75;
    if (g_ankh_config.get(CONFIG_UI_COMPLETE_RATING_COLUMNS)) {
        if (has_reached && value < 25)
            value_to_draw = 25;
    } else {
        // Default behaviour: not completing too small columns
        //        if (value < 30)
        //            has_reached = 0;
    }

    image_desc img_base{ GROUP_RATINGS_COLUMN };
    image_desc img_body{ GROUP_RATINGS_COLUMN, 1 };
    int y = image_get(img_base)->height;
    ui.image(img_base, pos + vec2i{ -4, y });
    for (int i = 0; i < 2 * value_to_draw; i++) {
        ui.image(img_body, pos + vec2i{ 11, --y });
    }

    image_desc img_top{ GROUP_RATINGS_COLUMN, 2 };
    if (has_reached) {
        ui.image(img_top, pos + vec2i{ -6, y - 50 });
    }
}

void ui::advisor_ratings_window::draw_rating(int id, int value, int open_play, int goal) {
    int enabled = !open_play && goal;
    pcstr idstr = rating_buttons[id];

    bstring64 btnid("rating_", idstr);
    ui[btnid].select(g_city.ratings.selected == (id + 1));
    ui[btnid] = ui::str(53, 1 + id);
    ui[btnid].onclick([id] {
        g_city.ratings.selected = id + 1;
    });

    bstring64 valueid("value_", idstr);
    ui[valueid].text_var("%u", value);

    bstring64 goalid("goal_", idstr);
    ui[goalid].text_var("%u %s", enabled ? goal : 0, ui::str(53, 5));
}

void ui::advisor_ratings_window::ui_draw_foreground(UiFlags flags) {
    ui.begin_widget(pos);
    ui.draw();

    int open_play = scenario_is_open_play();

    draw_rating_column(0, g_city.ratings.culture, open_play, winning_culture());
    draw_rating_column(1, g_city.ratings.prosperity, open_play, winning_prosperity());
    draw_rating_column(2, g_city.ratings.monument, open_play, winning_monuments());
    draw_rating_column(3, g_city.ratings.kingdom, open_play, winning_kingdom());

    ui.end_widget();
}

int ui::advisor_ratings_window::draw_background(UiFlags flags) {
    autoconfig_window::draw_background(flags);

    bstring128 caption = ui::str(53, 7);
    if (!(!winning_population() || scenario_is_open_play())) {
        caption = ui::str(53, 6);
        caption.append("%u", winning_population());
    }
    ui["population_label"] = caption;

    switch (g_city.ratings.selected) {
    case e_selected_rating_culture:
        ui["advice_header"] = ui::str(53, 1);
        ui["advice_text"] = (g_city.ratings.culture <= 90)
            ? ui::str(53, 9 + g_city.ratings.selected_explanation())
            : ui::str(53, 50);
        break;

    case e_selected_rating_prosperity:
        ui["advice_header"] = ui::str(53, 2);
        ui["advice_text"] = (g_city.ratings.prosperity <= 90)
            ? ui::str(53, 16 + g_city.ratings.selected_explanation())
            : ui::str(53, 51);
        break;

    case e_selected_rating_monument:
        ui["advice_header"] = ui::str(53, 3);
        ui["advice_text"] = (g_city.ratings.monument <= 90) ? ui::str(53, 41 + g_city.ratings.selected_explanation()) : ui::str(53, 52);
        break;

    case e_selected_rating_kingdom:
        ui["advice_header"] = ui::str(53, 4);
        ui["advice_text"] = (g_city.ratings.kingdom <= 90) ? ui::str(53, 27 + g_city.ratings.selected_explanation()) : ui::str(53, 53);
        break;

    default:
        ui["advice_text"] = ui::str(53, 8);
        break;
    }

    int open_play = scenario_is_open_play();

    draw_rating(0, g_city.ratings.culture, open_play, winning_culture());
    draw_rating(1, g_city.ratings.prosperity, open_play, winning_prosperity());
    draw_rating(2, g_city.ratings.monument, open_play, winning_monuments());
    draw_rating(3, g_city.ratings.kingdom, open_play, winning_kingdom());

    return 0;
}

advisor_window* ui::advisor_ratings_window::instance() {
    return &g_advisor_rating_window;
}
