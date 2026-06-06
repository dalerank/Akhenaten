#include "game_config.h"

#include "game/game.h"
#include "core/calc.h"
#include "js/js_game.h"
#include "core/profiler.h"
#include "widget/debug_console.h"

std::optional<bvariant> __game_feature_get(xstring feature_name) {
    auto feature = game_features::find(feature_name);
    if (feature) {
        switch (feature->type()) {
        case setting_bool: return bvariant(feature->to_bool());
        case setting_string: return bvariant(feature->to_string());
        case setting_float: return bvariant(feature->to_float());
        case setting_vec2i: return bvariant(feature->to_vec2i());
        default: break;
        }
    }
    return std::nullopt;
}
ANK_FUNCTION_1(__game_feature_get)

int __game_features_count() {
    return game_features::all().size();
}
ANK_FUNCTION(__game_features_count)

xstring __game_feature_name(int index) {
    auto all = game_features::all();
    if (index < 0 || index >= (int)all.size())
        return {};

    return all[index]->name;
}
ANK_FUNCTION_1(__game_feature_name)

xstring __game_feature_text(xstring feature_name) {
    auto feature = game_features::find(feature_name);
    return feature ? feature->text : xstring("<unknown>");
}
ANK_FUNCTION_1(__game_feature_text)

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
        case setting_float: {
            float f = 0.f;
            if (value.is_float()) {
                f = value.as_float();
            } else if (value.is_int32()) {
                f = (float)value.as_int32();
            } else if (value.is_uint32()) {
                f = (float)value.as_uint32();
            } else {
                f = value.float_or_def(0.f);
            }
            feature->set(f);
            break;
        }
        case setting_vec2i:
            if (value.is_vec2i()) {
                feature->set(value.as_vec2i());
            }
            break;
        default:
            break;
        }
    }
}
ANK_FUNCTION_2(__game_feature_set)

int __game_feature_type(xstring feature_name) {
    auto feature = game_features::find(feature_name);
    return feature ? (int)feature->type() : (int)setting_none;
}
ANK_FUNCTION_1(__game_feature_type)

xstring __game_feature_type_name(int type) {
    pcstr name = e_setting_variant_type_tokens.name((setting_variant_type)type);
    return name ? xstring(name) : xstring("unknown");
}
ANK_FUNCTION_1(__game_feature_type_name)

std::optional<bvariant> __game_feature_default(xstring feature_name) {
    auto feature = game_features::find(feature_name);
    if (!feature) {
        return std::nullopt;
    }

    const setting_variant &def = feature->defaultv;
    if (std::holds_alternative<bool>(def)) {
        return bvariant(std::get<bool>(def));
    }
    if (std::holds_alternative<float>(def)) {
        return bvariant(std::get<float>(def));
    }
    if (std::holds_alternative<vec2i>(def)) {
        return bvariant(std::get<vec2i>(def));
    }
    if (std::holds_alternative<xstring>(def)) {
        return bvariant(std::get<xstring>(def));
    }
    return std::nullopt;
}
ANK_FUNCTION_1(__game_feature_default)

void __debug_feature_bool(xstring feature_name, xstring display_name) {
    auto feature = game_features::find(feature_name);
    if (!feature || feature->type() != setting_bool) {
        return;
    }

    bool current = feature->to_bool();
    bool saved = current;
    pcstr label = display_name.empty() ? feature->name.c_str() : display_name.c_str();
    game_debug_show_property(label, current);
    if (saved != current) {
        feature->set(current);
    }
}
ANK_FUNCTION_2(__debug_feature_bool)