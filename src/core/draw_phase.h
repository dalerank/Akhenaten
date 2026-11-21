#pragma once

namespace draw_phase {
    void enter();
    void leave();
    bool active();
    void check_write(const char* where);

    struct scope {
        scope() { enter(); }
        ~scope() { leave(); }
    };

    struct allow_writes {
        allow_writes();
        ~allow_writes();
    };
} // namespace draw_phase
