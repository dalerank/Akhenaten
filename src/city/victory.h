#pragma once

enum e_victory_state {
    e_victory_state_lost = -1,
    e_victory_state_none = 0,
    e_victory_state_won = 1
};

struct vistory_state_t {
    e_victory_state state;
    bool force_win;
    bool force_lost;
    
    void reset();
    void update_months_to_govern();
    void continue_governing(int months);
    void stop_governing();
    bool has_won();
};





