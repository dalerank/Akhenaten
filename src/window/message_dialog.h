#pragma once

#include "core/xstring.h"

enum e_message_dialog_type {
    MESSAGE_DIALOG_ABOUT = 0,
    MESSAGE_DIALOG_HELP = 10,
    MESSAGE_DIALOG_TOP_FUNDS = 15,
    MESSAGE_DIALOG_TOP_POPULATION = 16,
    MESSAGE_DIALOG_TOP_DATE = 17,
    MESSAGE_DIALOG_OVERLAYS = 18,
    MESSAGE_DIALOG_ADVISOR_LABOR = 20,
    MESSAGE_DIALOG_ADVISOR_MILITARY = 21,
    MESSAGE_DIALOG_ADVISOR_IMPERIAL = 22,
    MESSAGE_DIALOG_ADVISOR_RATINGS = 23,
    MESSAGE_DIALOG_ADVISOR_TRADE = 24,
    MESSAGE_DIALOG_ADVISOR_POPULATION = 25,
    MESSAGE_DIALOG_ADVISOR_HEALTH = 26,
    MESSAGE_DIALOG_ADVISOR_EDUCATION = 27,
    MESSAGE_DIALOG_ADVISOR_ENTERTAINMENT = 28,
    MESSAGE_DIALOG_ADVISOR_RELIGION = 29,
    MESSAGE_DIALOG_ADVISOR_FINANCIAL = 30,
    MESSAGE_DIALOG_ADVISOR_CHIEF = 31,
    MESSAGE_DIALOG_EMPIRE_MAP = 32,
    MESSAGE_DIALOG_MESSAGES = 34,
    MESSAGE_DIALOG_GOD_UPSET = 35,
    MESSAGE_DIALOG_INDUSTRY = 46,
    MESSAGE_DIALOG_THEFT = 251,
    MESSAGE_DIALOG_EDITOR_ABOUT = 331,
    MESSAGE_DIALOG_EDITOR_HELP = 332,
};

struct text_tag_substitution {
    xstring tag;
    xstring content;
} ;

void text_fill_in_tags(pcstr src, pstr dst, text_tag_substitution* tag_templates, int num_tags);

void window_message_dialog_show(xstring text_id, int message_id, void (*background_callback)(void));

void window_message_dialog_show_city_message(xstring text_id, int message_id, int year, int month, int param1, int param2, int message_advisor, bool use_popup);