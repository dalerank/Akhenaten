#include "city/city_message.h"

#include "js/js_game.h"
#include "js/js_global_object.h"

ANK_GLOBAL_OBJECT(g_message_manager, __city_messages,
    consecutive_message_delay,
    next_message_sequence,
    total_messages,
    current_message_id,
    problem_count,
    problem_index);
