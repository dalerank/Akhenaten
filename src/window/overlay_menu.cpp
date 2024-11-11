#include "overlay_menu.h"

#include "core/time.h"
#include "game/state.h"
#include "overlays/city_overlay.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/view/view.h"
#include "graphics/elements/panel.h"
#include "graphics/view/view.h"
#include "graphics/window.h"
#include "input/input.h"
#include "io/gamefiles/lang.h"
#include "window/window_city.h"
#include "widget/widget_sidebar.h"
#include "game/game.h"

static void button_menu_item(int index, int param2);
static void button_submenu_item(int index, int param2);

static generic_button menu_buttons[] = {
  {0, 0, 160, 24, button_menu_item, button_none, 0, 0},
  {0, 24, 160, 24, button_menu_item, button_none, 1, 0},
  {0, 48, 160, 24, button_menu_item, button_none, 2, 0},
  {0, 72, 160, 24, button_menu_item, button_none, 3, 0},
  {0, 96, 160, 24, button_menu_item, button_none, 4, 0},
  {0, 120, 160, 24, button_menu_item, button_none, 5, 0},
  {0, 144, 160, 24, button_menu_item, button_none, 6, 0},
  {0, 168, 160, 24, button_menu_item, button_none, 7, 0},
  {0, 192, 160, 24, button_menu_item, button_none, 8, 0},
  {0, 216, 160, 24, button_menu_item, button_none, 9, 0},
};

static generic_button submenu_buttons[] = {
  {0, 0, 160, 24, button_submenu_item, button_none, 0, 0},
  {0, 24, 160, 24, button_submenu_item, button_none, 1, 0},
  {0, 48, 160, 24, button_submenu_item, button_none, 2, 0},
  {0, 72, 160, 24, button_submenu_item, button_none, 3, 0},
  {0, 96, 160, 24, button_submenu_item, button_none, 4, 0},
  {0, 120, 160, 24, button_submenu_item, button_none, 5, 0},
  {0, 144, 160, 24, button_submenu_item, button_none, 6, 0},
  {0, 168, 160, 24, button_submenu_item, button_none, 7, 0},
  {0, 192, 160, 24, button_submenu_item, button_none, 8, 0},
  {0, 216, 160, 24, button_submenu_item, button_none, 9, 0},
};

static const int MENU_ID_TO_OVERLAY[8] = {
    OVERLAY_NONE,
    OVERLAY_WATER,
    1,
    3,
    5,
    6,
    7,
    OVERLAY_RELIGION
};

static const int MENU_ID_TO_SUBMENU_ID[8] = {0, 0, 1, 2, 3, 4, 5, 6};

static const int submenu_id_to_overlay[7][8] = {
  {0},
  
  { // Risks
   OVERLAY_FIRE,
   OVERLAY_DAMAGE,
   OVERLAY_CRIME,
   OVERLAY_NATIVE,
   OVERLAY_PROBLEMS,
   OVERLAY_LABOR,
   OVERLAY_ROUTING,
   0},
  
  { // Entertainment
   OVERLAY_ENTERTAINMENT,
   OVERLAY_BOOTH,
   OVERLAY_BANDSTAND,
   OVERLAY_PAVILION,
   OVERLAY_SENET_HOUSE,
   0},

  { // Education
   OVERLAY_EDUCATION,
   OVERLAY_SCRIBAL_SCHOOL,
   OVERLAY_LIBRARY,
   OVERLAY_ACADEMY,
   0},
  
  { // Health 
   OVERLAY_HEALTH,
   OVERLAY_APOTHECARY,
   OVERLAY_DENTIST,
   OVERLAY_MORTUARY,
   OVERLAY_PHYSICIAN,
   0},
  
  { // Administration
   OVERLAY_TAX_INCOME,
   OVERLAY_COUTHOUSE,
   OVERLAY_FOOD_STOCKS,
   OVERLAY_BAZAAR_ACCESS,
   OVERLAY_DESIRABILITY,
   OVERLAY_FERTILITY,
   0},

  {// Religion
   OVERLAY_RELIGION,
   OVERLAY_RELIGION_OSIRIS,
   OVERLAY_RELIGION_RA,
   OVERLAY_RELIGION_PTAH,
   OVERLAY_RELIGION_SETH,
   OVERLAY_RELIGION_BAST,
   0},
};

struct overlay_menu_data_t {
    int selected_menu;
    int selected_submenu;
    int num_submenu_items;
    time_millis submenu_focus_time;

    int menu_focus_button_id;
    int submenu_focus_button_id;

    int keep_submenu_open;
};

overlay_menu_data_t g_overlay_menu_data;

static void init() {
    auto& data = g_overlay_menu_data;
    data.selected_submenu = 0;
    data.num_submenu_items = 0;   
}

static void window_overlay_draw_background() {
    window_city_draw_panels();
    widget_sidebar_city_draw_foreground();
}

static int get_sidebar_x_offset() {
    vec2i view_pos, view_size;
    const view_data_t &viewport = city_view_viewport();
    city_view_get_viewport(viewport, view_pos, view_size);

    return view_pos.x + view_size.x;
}

const char* game_state_overlay_text(int index) {
    switch (index) {
    case OVERLAY_RELIGION_OSIRIS:
        return "Osiris";
    case OVERLAY_RELIGION_RA:
        return "Ra";
    case OVERLAY_RELIGION_PTAH:
        return "Ptah";
    case OVERLAY_RELIGION_SETH:
        return "Seth";
    case OVERLAY_RELIGION_BAST:
        return "Bast";
    case OVERLAY_NATIVE:
        return "Native";
    case OVERLAY_FERTILITY:
        return "Fertility";
    case OVERLAY_DESIRABILITY:
        return "Desirability";
    case OVERLAY_TAX_INCOME:
        return "Tax income";
    case OVERLAY_FOOD_STOCKS:
        return "Food stocks";
    case OVERLAY_BAZAAR_ACCESS:
        return "Bazaar access";
    case OVERLAY_ROUTING:
        return "Routing";
    case OVERLAY_HEALTH: 
        return "Health";
    case OVERLAY_APOTHECARY: 
        return "Apothecary";
    case OVERLAY_MORTUARY:
        return "Mortuary";
    case OVERLAY_DENTIST:
        return "Dentist";
    case OVERLAY_PROBLEMS:
        return "Problems";
    case OVERLAY_LABOR:
        return "Labor";
    case OVERLAY_COUTHOUSE:
        return "Magistrate";
    }

    return (const char*)lang_get_string(e_text_overlay_menu, index);
}

static void window_overlay_draw_foreground() {
    painter ctx = game.painter();
    auto& data = g_overlay_menu_data;
    window_city_draw();
    int x_offset = get_sidebar_x_offset();

    for (int i = 0; i < 8; i++) {
        label_draw(x_offset - 170, 74 + 24 * i, 10, data.menu_focus_button_id == i + 1 ? 1 : 2);
        lang_text_draw_centered(14, MENU_ID_TO_OVERLAY[i], x_offset - 170, 77 + 24 * i, 160, FONT_NORMAL_BLACK_ON_DARK);
    }

    if (data.selected_submenu > 0) {
        ImageDraw::img_generic(ctx, image_id_from_group(PACK_GENERAL, 158), x_offset - 185, 80 + 24 * data.selected_menu);
        for (int i = 0; i < data.num_submenu_items; i++) {
            label_draw(x_offset - 348, 74 + 24 * (i + data.selected_menu), 10, data.submenu_focus_button_id == i + 1 ? 1 : 2);

            const char* text = game_state_overlay_text(submenu_id_to_overlay[data.selected_submenu][i]);
            text_draw_centered((uint8_t*)text, x_offset - 348, 77 + 24 * (i + data.selected_menu), 160, FONT_NORMAL_BLACK_ON_DARK, 0);
        }
    }
}

static int count_submenu_items(int submenu_id) {
    int total = 0;
    for (int i = 0; i < 8 && submenu_id_to_overlay[submenu_id][i] > 0; i++) {
        total++;
    }
    return total;
}

static void open_submenu(int index, int keep_open) {
    auto& data = g_overlay_menu_data;
    data.keep_submenu_open = keep_open;
    data.selected_menu = index;
    data.selected_submenu = MENU_ID_TO_SUBMENU_ID[index];
    data.num_submenu_items = count_submenu_items(data.selected_submenu);
}

static void close_submenu(void) {
    auto& data = g_overlay_menu_data;
    if (data.selected_menu || data.selected_submenu) {
        data.keep_submenu_open = 0;
        data.selected_menu = 0;
        data.selected_submenu = 0;
        data.num_submenu_items = 0;
    }
}

static void window_overlay_handle_submenu_focus(void) {
    auto& data = g_overlay_menu_data;
    if (data.menu_focus_button_id || data.submenu_focus_button_id) {
        data.submenu_focus_time = time_get_millis();
        if (data.menu_focus_button_id) {
            open_submenu(data.menu_focus_button_id - 1, 0);
        }
    } else if (time_get_millis() - data.submenu_focus_time > 500) {
        close_submenu();
    }
}

static void window_overlay_handle_input(const mouse* m, const hotkeys* h) {
    auto& data = g_overlay_menu_data;
    int x_offset = get_sidebar_x_offset();
    bool handled = false;
    handled |= !!generic_buttons_handle_mouse(m, {x_offset - 170, 72}, menu_buttons, 8, &data.menu_focus_button_id);

    if (!data.keep_submenu_open) {
        window_overlay_handle_submenu_focus();
    }

    if (data.selected_submenu) {
        handled |= !!generic_buttons_handle_mouse(m, {x_offset - 348, 72 + 24 * data.selected_menu}, submenu_buttons, data.num_submenu_items, &data.submenu_focus_button_id);
    }

    if (!handled && input_go_back_requested(m, h)) {
        if (data.keep_submenu_open)
            close_submenu();
        else {
            window_city_show();
        }
    }
}

static void button_menu_item(int index, int param2) {
    auto& data = g_overlay_menu_data;
    if (MENU_ID_TO_SUBMENU_ID[index] == 0) {
        game_state_set_overlay((e_overlay)MENU_ID_TO_OVERLAY[index]);
        close_submenu();
        window_city_show();
    } else {
        if (data.keep_submenu_open && data.selected_submenu == MENU_ID_TO_SUBMENU_ID[index])
            close_submenu();
        else {
            open_submenu(index, 1);
        }
    }
}

static void button_submenu_item(int index, int param2) {
    auto& data = g_overlay_menu_data;
    int overlay = submenu_id_to_overlay[data.selected_submenu][index];
    if (overlay) {
        game_state_set_overlay((e_overlay)overlay);
    }

    close_submenu();
    window_city_show();
}

void window_overlay_menu_show(void) {
    window_type window = {
        WINDOW_OVERLAY_MENU,
        window_overlay_draw_background,
        window_overlay_draw_foreground,
        window_overlay_handle_input
    };
    init();
    window_show(&window);
}
