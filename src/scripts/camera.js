log_info("akhenaten: camera info started")

camera_zoom {
    zoom_default : 100
    zoom_min : 25
    zoom_max : 250
    zoom_epsilon : 0.05
    zoom_lerp_coeff : 0.05
    zoom_speed : 26
}

[es=event_rotate_map]
function camera_on_rotate_map(ev) {
    if (ev.value === HOTKEY_ROTATE_MAP_LEFT) {
        __city_view_rotate_left()
    }

    if (ev.value === HOTKEY_ROTATE_MAP_RIGHT) {
        __city_view_rotate_right()
    }
}

[es=event_rotate_map_reset]
function camera_on_rotate_map_reset(ev) {
    __city_view_rotate_north()
}