#include "window_advisors.h"

#include "js/js_game.h"

ANK_FUNCTION(window_advisors_show_checked)

namespace js_helpers {
    template<>
    inline e_advisor js_to_value<e_advisor>(js_State *J, int idx) {
        return (e_advisor)js_tointeger(J, idx);
    }
}
ANK_FUNCTION_1(window_advisors_show_advisor)