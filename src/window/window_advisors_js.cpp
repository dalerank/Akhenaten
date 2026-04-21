#include "window_advisors.h"

#include "js/js_game.h"
#include "core/profiler.h"

ANK_FUNCTION(window_advisors_show)

namespace js_helpers {
    template<>
    inline e_advisor js_to_value<e_advisor>(js_State *J, int idx) {
        return (e_advisor)js_tointeger(J, idx);
    }
}