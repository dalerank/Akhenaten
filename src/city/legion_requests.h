#pragma once

enum {
    LEGION_STRENGTH_BASE = 100,
    CHARIOTEER_STRENGTH_BASE = 200,
    WARSHIP_STRENGTH_DIVISOR = 10,
    REQUEST_LOSSES_ALL = 100,
};

int figure_warship_request_strength(int figure_id);
int formation_request_strength(int request_id, int *warships_out, int *legions_out);
int figure_find_legion_transport_ship(int formation_id);
bool formation_legion_is_on_ship(int formation_id);

void formation_legions_dispatch_to_request(int event_id);
void formation_legions_return_from_request(int event_id);
void formation_legions_request_losses(int percentage, int event_id);
