#include "window_editor.h"

#include "editor/editor.h"
#include "editor/tool.h"
#include "game/game.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/text.h"
#include "graphics/view/view.h"
#include "graphics/window.h"
#include "game/game_config.h"
#include "widget/map_editor.h"
#include "widget/sidebar/editor.h"
#include "widget/top_menu_editor.h"
#include "window/editor/attributes.h"
#include "window/file_dialog.h"
#include "window/popup_dialog.h"
#include "platform/renderer.h"

static int city_view_dirty;

static void draw_background(int) {
    g_render.clear_screen();
    widget_sidebar_editor_draw_background();
    widget_top_menu_editor_draw();
}

static void draw_cancel_construction() {
    painter ctx = game.painter();
    if (!mouse::get().is_touch || !editor_tool_is_active()) {
        return;
    }
    vec2i view_pos, view_size;
    city_view_get_viewport(g_city_view, view_pos, view_size);
    view_size.x -= 4 * 16;
    inner_panel_draw({ view_size.x - 4, 40 }, { 3, 2 });
    ctx.img_generic(image_id_from_group(GROUP_OK_CANCEL_SCROLL_BUTTONS) + 4, vec2i{view_size.x, 44});
    city_view_dirty = 1;
}

static void clear_city_view() {
    if (city_view_dirty) {
        g_render.clear_screen();
    }

    city_view_dirty = 0;
}

static void draw_foreground(int) {
    clear_city_view();
    widget_sidebar_editor_draw_foreground();
    widget_map_editor_draw();
    if (window_is(WINDOW_EDITOR_MAP))
        draw_cancel_construction();
}

static void handle_hotkeys(const hotkeys* h) {
    //if (h->load_file)
    //    window_file_dialog_show(FILE_TYPE_SCENARIO, FILE_DIALOG_LOAD);

    //if (h->save_file)
    //    window_file_dialog_show(FILE_TYPE_SCENARIO, FILE_DIALOG_SAVE);
}

static void handle_input(const mouse* m, const hotkeys* h) {
    handle_hotkeys(h);
    if (widget_top_menu_editor_handle_input(m, h))
        return;
    if (widget_sidebar_editor_handle_mouse(m))
        return;
    widget_map_editor_handle_input(m, h);
}

void window_editor_map_draw_all(void) {
    draw_background(0);
    draw_foreground(0);
}

void window_editor_map_draw_panels(void) {
    draw_background(0);
}

void window_editor_map_draw(void) {
    widget_map_editor_draw();
}

void window_editor_map_show(void) {
    static window_type window = {
        WINDOW_EDITOR_MAP,
        draw_background,
        draw_foreground,
        handle_input
    };
    window_show(&window);
}
