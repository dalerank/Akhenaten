#include "window_info_storageyard.h"

#include "window/building/distribution.h"
#include "window/building/common.h"
#include "building/building_storage_yard.h"
#include "city/city_resource.h"
#include "graphics/window.h"
#include "graphics/screen.h"
#include "input/input.h"
#include "game/game.h"

vec2i info_window_storageyard_orders::get_adjusted_offset(object_info *c) {
    vec2i desired_offset = c->offset + parent_window_offset;
    vec2i bgsize_px = ui["background"].pxsize();
    
    // Проверяем, не выходит ли окно за верхнюю границу экрана
    if (desired_offset.y < MIN_Y_POSITION) {
        desired_offset.y = MIN_Y_POSITION;
    }
    
    // Проверяем, не выходит ли окно за нижнюю границу экрана
    int screen_bottom = screen_height() - MARGIN_POSITION;
    if (desired_offset.y + bgsize_px.y > screen_bottom) {
        desired_offset.y = screen_bottom - bgsize_px.y;
        // Если после корректировки окно все еще выходит за верхнюю границу, 
        // размещаем его у верхней границы
        if (desired_offset.y < MIN_Y_POSITION) {
            desired_offset.y = MIN_Y_POSITION;
        }
    }
    
    return desired_offset;
}

void info_window_storageyard_orders::draw_background(object_info *c) {
    auto *storage = c->building_get()->dcast_storage_yard();
    int storage_id = storage->storage_id();
    ui["empty_all"] = storage->is_empty_all() ? ui::str(99, 5) : ui::str(99, 4);

    ui["empty_all"].onclick([storage_id] {
        building_storage_toggle_empty_all(storage_id);
    });

    ui["accept_none"].onclick([storage_id] {
        building_storage_accept_none(storage_id);
    });
}

void info_window_storageyard_orders::draw_foreground(object_info *c) {
    building_info_window::window_info_background(*c);

    const resource_list resources = g_city.resource.available();
    auto &data = g_window_building_distribution;

    auto *b = c->building_get();
    auto *storageyard = b->dcast_storage_yard();
    int storage_id = storageyard->storage_id();
    auto storage = storageyard->storage();
    backup_storage_settings(storage_id);

    vec2i adjusted_offset = get_adjusted_offset(c);
    ui.begin_widget(adjusted_offset - c->offset, true);
    ui.draw();

    vec2i offset = ui["resource_base"].pos;
    vec2i icon_column = ui["icon_column"].pos;
    vec2i name_column = ui["name_column"].pos;
    vec2i increase_column = ui["increase_column"].pos;
    vec2i decrease_column = ui["decrease_column"].pos;
    auto &order_column = ui["order_column"];
    vec2i item_offset = ui["item_row"].size;
    vec2i bgsize = ui["background"].pxsize();

    int line_y = 0;
    struct storage_res {
        e_resource resource;
        int storage_id;
    };
    for (const auto &r : resources) {
        line_y += item_offset.y;

        ui.icon(offset + icon_column + vec2i{0, line_y}, r.type);
        ui.label(ui::str(23, r.type), offset + name_column + vec2i{ 0, line_y }, FONT_NORMAL_WHITE_ON_DARK);

        auto status = window_building_get_order_instruction(INSTR_STORAGE_YARD, *storage, r.type);
        ui.button(status.first, offset + order_column.pos + vec2i{ 0, line_y }, order_column.pxsize(), fonts_vec{ status.second }, UiFlags_NoBody | UiFlags_AlignYCentered)
            .onclick([storage_id, resource = r.type] {
                building_storage_cycle_resource_state(storage_id, resource, false);
            })
            .onrclick([resource = r.type, storage_id] {
                building_storage_cycle_resource_state(storage_id, resource, true);
            });

        // arrows
        int state = storage->resource_state[r.type];
        if (state == STORAGE_STATE_PHARAOH_ACCEPT || state == STORAGE_STATE_PHARAOH_GET) {
            ui.arw_button(offset + increase_column + vec2i(0, line_y), true, true)
                .onclick([storage_id, resource = r.type] {
                    building_storage_increase_decrease_resource_state(storage_id, resource, true);
                });

            ui.arw_button(offset + decrease_column + vec2i(0, line_y), false, true)
                .onclick([storage_id, resource = r.type] {
                    building_storage_increase_decrease_resource_state(storage_id, resource, false);
                });
        }
    }

    ui.end_widget();
}

int info_window_storageyard_orders::window_info_handle_mouse(const mouse *m, object_info &c) {
    vec2i adjusted_offset = get_adjusted_offset(&c);
    ui.begin_widget(adjusted_offset, true);
    int result = ui.handle_mouse(m);
    ui.end_widget();

    const hotkeys *h = hotkey_state();
    if (!result && input_go_back_requested(m, h)) {
        storage_settings_backup_check();
        events::emit(event_show_tile_info{ tile2i(c.grid_offset), /*avoid_mouse*/true, SOURCE_LOCATION });
        return -1;
    }
    
    return result;
}