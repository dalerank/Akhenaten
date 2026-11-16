#pragma once

#include "core/xstring.h"
#include "figure/figure_type.h"

using sound_key = xstring;

struct event_synthesize_figure_phrase {
    int id;
    xstring path;
    xstring text;
};

inline constexpr pcstr FIGURE_PHRASE_WAITING = "waiting_for_phrase";

struct sound_key_state {
    sound_key prefix;
    bool valid;
};

class figure;

inline constexpr int FIGURE_PHRASE_NONE = -1;

// Types that OG gives a phrase rule; the others keep their script phrase.
bool figure_phrase_is_og(e_figure_type type);
// Types that talk about the city's problems and show the "tell me more" button (OG building_info.c figure_speaks).
bool figure_phrase_speaks(e_figure_type type);
void figure_phrase_determine(figure& f);
// OG speech id (201..) of the figure's phrases, or -1.
int figure_phrase_speech_id(const figure& f);
xstring figure_phrase_sound_file(const figure& f);
xstring figure_phrase_text(const figure& f);
void figure_phrase_apply(figure& f);
bool figure_phrase_has_other_problem(const figure& f);
void figure_phrase_next_problem(figure& f);
int figure_phrase_advisor(const figure& f);
