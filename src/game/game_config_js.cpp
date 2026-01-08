#include "game_config.h"

#include "js/js_game.h"

std::optional<bvariant> __game_feature_get(xstring feature_name) {
    auto feature = game_features::find(feature_name);
    if (feature) {
        switch (feature->type()) {
        case setting_bool: return bvariant(feature->to_bool());
        case setting_string: return bvariant(feature->to_string());
        }
    }
    return std::nullopt;
}
ANK_FUNCTION_1(__game_feature_get)

void __game_feature_set(xstring feature_name, bvariant value) {
    auto feature = game_features::find(feature_name);
    if (feature) {
        switch (feature->type()) {
        case setting_bool: {
            // Convert value to bool - handle both bool and int types
            bool bool_value;
            if (value.is_bool()) {
                bool_value = value.as_bool();
            } else if (value.is_int32()) {
                bool_value = value.as_int32() != 0;
            } else if (value.is_uint32()) {
                bool_value = value.as_uint32() != 0;
            } else {
                // Default to false if type is unknown
                bool_value = false;
            }
            feature->set(bool_value);
            break;
        }
        case setting_string: feature->set(value.as_str()); break;
        }
    }
}
ANK_FUNCTION_2(__game_feature_set)