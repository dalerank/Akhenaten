#pragma once

#include "core/archive.h"
#include "core/svector.h"
#include "core/tokenum.h"
#include "core/vec2i.h"

// OG empire_window.c:615-664: the invasions and the troops sent abroad, walking their routes on the empire map.
enum e_empire_marker_kind : uint8_t {
    EMPIRE_MARKER_INVASION = 0,
    EMPIRE_MARKER_TROOPS_AWAY = 1,
    EMPIRE_MARKER_TROOPS_RETURN = 2,
    EMPIRE_MARKER_MAX
};
using e_empire_marker_kind_tokens_t = token_holder<e_empire_marker_kind, EMPIRE_MARKER_INVASION, EMPIRE_MARKER_MAX>;
extern const e_empire_marker_kind_tokens_t e_empire_marker_kind_tokens;

struct empire_marker_t {
    int event_id = -1;
    int kind = EMPIRE_MARKER_INVASION;
    bool by_sea = false;
    vec2i pos;  // empire map pixels, the top left of the marker image
    vec2i size; // of the image as drawn (OG draw_marker records it for the pick)
};
ANK_CONFIG_PROPERTY(empire_marker_t, event_id, kind, by_sea, pos)

struct empire_markers_rules_t {
    int anim_counter_max = 0;
    int anim_offset_start = 0;
    int anim_offset_divisor = 1;
    int pick_distance = 0;
};
ANK_CONFIG_STRUCT(empire_markers_rules_t, anim_counter_max, anim_offset_start, anim_offset_divisor, pick_distance)
extern empire_markers_rules_t empire_markers_rules;

struct empire_markers_t {
    enum { MAX_MARKERS = 92 }; // OG EMPIRE_EVENT_MARKERS

    svector<empire_marker_t, MAX_MARKERS> markers;
    int anim_counter = 0;
    int selected_event = -1;

    // Once per drawn frame of the empire map, as OG window_empire_draw_map.
    void update();
    void rebuild();
    void set_size(int index, vec2i size);
    // OG empire_map_object_at_mouse: true when a marker is nearer than `object_distance`.
    bool select(vec2i map_pos, int object_distance);
    void clear_selection() { selected_event = -1; }
    const empire_marker_t* selected() const;

private:
    void add_invasions();
    void add_troops();
};

extern empire_markers_t g_empire_markers;
