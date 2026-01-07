#include "game_config.h"

#include "js/js_game.h"

std::optional<bvariant> __game_feature_get(xstring feature_name) {
    auto feature = game_features::find(feature_name);
    if (feature) {
        switch (feature->type()) {
        case setting_bool:
            return bvariant(feature->to_bool());

        case setting_string:
            return bvariant(feature->to_string());
        }
    }
    return std::nullopt;
}
ANK_FUNCTION_1(__game_feature_get)