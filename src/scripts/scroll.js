log_info("akhenaten: scroll_config started")

scroll_config {
    mouse_border: 5
    touch_border: 100
    drag_min_delta: 4
    drag_decay_time: 350
    regular_decay_time: 75
    key_wait_time_after_hold: 500
    key_pressed: 1
    key_max_value: 30000.0
    tile_x_pixels: 60
    tile_y_pixels: 30
    mouse_pan_log_k: 0.052
    direction_x: [0, 1, 1, 1, 0, -1, -1, -1, 0]
    direction_y: [-1, -1, 0, 1, 1, 1, 0, -1, 0]
    step_city: [60, 44, 30, 20, 16, 12, 10, 8, 6, 4, 2]
    step_empire: [20, 15, 10, 7, 5, 4, 3, 3, 2, 2, 1]
}
