#include "building_storage.h"
#include "building/building.h"
#include "js/js_game.h"
#include "core/profiler.h"
#include "graphics/elements/ui.h"
#include "graphics/elements/arrow_button.h"

int __storage_yard_storage_id(int bid) {
    building *raw = building_get(bid);
    if (!raw) { return 0; }
    auto b = raw->dcast_storage();
    return b ? b->storage_id() : 0;
}
ANK_FUNCTION_1(__storage_yard_storage_id)

bool __storage_yard_is_empty_all(int storage_id) {
    const storage_t *s = building_storage_get(storage_id);
    return s ? (bool)s->empty_all : false;
}
ANK_FUNCTION_1(__storage_yard_is_empty_all)

int __storage_yard_resource_state(int storage_id, int resource_id) {
    const storage_t *s = building_storage_get(storage_id);
    return s ? s->resource_state[resource_id] : 0;
}
ANK_FUNCTION_2(__storage_yard_resource_state)

int __storage_yard_resource_max_accept(int storage_id, int resource_id) {
    const storage_t *s = building_storage_get(storage_id);
    return s ? s->resource_max_accept[resource_id] : 0;
}
ANK_FUNCTION_2(__storage_yard_resource_max_accept)

int __storage_yard_resource_max_get(int storage_id, int resource_id) {
    const storage_t *s = building_storage_get(storage_id);
    return s ? s->resource_max_get[resource_id] : 0;
}
ANK_FUNCTION_2(__storage_yard_resource_max_get)

void __storage_yard_toggle_empty_all(int storage_id) {
    building_storage_toggle_empty_all(storage_id);
}
ANK_FUNCTION_1(__storage_yard_toggle_empty_all)

void __storage_yard_accept_none(int storage_id) {
    building_storage_accept_none(storage_id);
}
ANK_FUNCTION_1(__storage_yard_accept_none)

void __storage_yard_cycle_resource_state(int storage_id, int resource_id, bool backwards) {
    building_storage_cycle_resource_state(storage_id, resource_id, backwards);
}
ANK_FUNCTION_3(__storage_yard_cycle_resource_state)

void __storage_yard_increase_decrease_resource_state(int storage_id, int resource_id, bool increase) {
    building_storage_increase_decrease_resource_state(storage_id, resource_id, increase);
}
ANK_FUNCTION_3(__storage_yard_increase_decrease_resource_state)

void __storage_yard_draw_arw_button(int pos_x, int pos_y, bool down, int storage_id, int resource_id, bool increase) {
    auto &btn = ui::arw_button({pos_x, pos_y}, down, true);
    btn.onclick([storage_id, resource_id, increase] {
        building_storage_increase_decrease_resource_state(storage_id, resource_id, increase);
    });
}
ANK_FUNCTION_6(__storage_yard_draw_arw_button)
