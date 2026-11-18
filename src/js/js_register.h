#pragma once

#include "core/archive.h"
#include "core/bstring.h"
#include "core/core.h"
#include "core/hvector.h"
#include "core/typename.h"
#include "core/variant.h"
#include "core/xstring.h"
#include "js/js_constants.h"
#include "js/js_struct.h"

#include <algorithm>
#include <cstring>

struct js_State;
class settings_vars_t;

namespace config {

    using jsfunc_iterator_function_cb = void(js_State*);
    using FunctionIterator = FuncLinkedList<jsfunc_iterator_function_cb*, ConfigTag>;

    struct TestConfigTag {};
    using TestFunctionIterator = FuncLinkedList<jsfunc_iterator_function_cb*, TestConfigTag>;

    struct ESIteratorEntry {
        xstring es_type;
        void (*regnew)(pcstr name);
        void (*clear)();
        ESIteratorEntry* next;
        static ESIteratorEntry* tail;
        ESIteratorEntry(pcstr t, void (*cb)(pcstr), void (*cl)()) : es_type(t), regnew(cb), clear(cl) {
            next = tail;
            tail = this;
        }
    };

    struct ModifierIteratorEntry {
        xstring modifier_key;
        void (*callback)(js_State* J, pcstr name, pcstr value);
        ModifierIteratorEntry* next;
        static ModifierIteratorEntry* tail;
        ModifierIteratorEntry(pcstr key, void (*cb)(js_State*, pcstr, pcstr)) : modifier_key(key), callback(cb) {
            next = tail;
            tail = this;
        }
    };

} // end namespace config

#define ANK_REGISTER_ES_ITERATOR(es_type, func, clear)                                             \
    static config::ESIteratorEntry ANK_CONFIG_CC1(es_iter_entry, __LINE__)(#es_type, func, clear);

#define ANK_REGISTER_MODIFIER_ITERATOR(modifier_key, func)                                              \
    static config::ModifierIteratorEntry ANK_CONFIG_CC1(mod_iter_entry, __LINE__)(#modifier_key, func);

// Test-binding TUs (src/js/test/) define this to config::TestFunctionIterator before any include,
// so their natives are registered only under --integraltests.
#ifndef ANK_JS_FUNCTION_REGISTRY
#define ANK_JS_FUNCTION_REGISTRY config::FunctionIterator
#endif

#define ANK_DECLARE_JSFUNCTION_ITERATOR(func)                                    \
    void func(js_State*);                                                        \
    namespace config {                                                           \
        int ANK_CONFIG_PULL_VAR_NAME(func) = 1;                                  \
    }                                                                            \
    static ANK_JS_FUNCTION_REGISTRY ANK_CONFIG_CC1(func_handler, __LINE__)(func)

#define ANK_CONFIG_ENUM(enumt)                                                                   \
    enumt;                                                                                       \
    void register_enum_##enumt(config::type_enum);                                               \
    namespace config {                                                                           \
        int ANK_CONFIG_PULL_VAR_NAME(register_enum_##enumt) = 1;                                 \
    }                                                                                            \
    static config::EnumIterator ANK_CONFIG_CC1(config_handler, __LINE__)(register_enum_##enumt); \
    void register_enum_##enumt(config::type_enum) {                                              \
        js_register_tokens(enumt);                                                               \
    }

#define REPLICATE_STATIC_PARAMS_FROM_CONFIG(class_name)         \
    class_name::model_type model_##class_name;                  \
    ANK_DECLARE_CONFIG_ITERATOR(config_load_model##class_name); \
    void config_load_model##class_name() {                      \
        call_unload_if_exists(model_##class_name);              \
        class_name::model_type::static_params_load();           \
        call_init_if_exists(model_##class_name);                \
    }

void js_register_mission_vars(const settings_vars_t& vars);
void js_unref_function(xstring onclick_ref);
void js_call_function(xstring onclick_ref);
void js_call_function_bool(xstring js_ref, bool param);
bvariant js_call_function(xstring js_ref, int param1, int param2);
bvariant js_call_function(xstring js_ref, const bvariant_map& params);
int js_game_emit_es(xstring es, xstring sub_event, bvariant_map args);
void js_register_game_handlers(xstring missionid);
void js_call_event_handlers(const xstring& event_name, const bvariant_map& object);
bool js_has_event_handlers(const xstring& event_name);
void js_register_entity_systems();

template <typename T>
inline void js_event(const T& ev, const xstring& evname_str) {
    if (!js_has_event_handlers(evname_str)) {
        return;
    }

    bvariant_map::scoped js_j;
    js_helper::writer(*js_j, ev);
    js_call_event_handlers(evname_str, *js_j);
}

namespace js_helpers {
    /** One identifier of a composite key. bstring64 truncates silently, and es_hash_str
     *  cannot detect it afterwards (it measures the parts it was handed), so check here.
     *  The parser applies the same 63-char limit to script-side identifiers. */
    inline bstring64 es2str_checked(pcstr es) {
        // An unset xstring yields a null c_str(); callers treat that as an empty
        // component and filter the miss themselves, so only guard against truncation.
        if (!es) {
            return {""};
        }
        verify_no_crash_var(strlen(es) < (size_t)bstring64::capacity,
          "es2str: identifier '%s' does not fit in %d bytes", es, (int)bstring64::capacity);
        return {es};
    }

    inline bstring64 es2str(pcstr es) {
        return es2str_checked(es);
    }
    inline bstring64 es2str(const xstring& es) {
        return es2str_checked(es.c_str());
    }
    inline bstring64 es2str(const cstring& es) {
        return es2str_checked(es.c_str());
    }

    template <size_t N>
    inline bstring64 es2str(const char (&es)[N]) {
        return es2str_checked(es);
    }

    template <typename ES>
    inline bstring64 es2str(const ES&) {
        type_name_holder<ES> esname;
        auto buf = type_enclosing_function_name(esname.value.data());
        return es2str_checked(buf);
    }

    /** Composite [es=(a, b)] key: identifiers sorted, joined with '+'.
     *  Must stay byte-identical to what parse_modifier_tuple_value builds in the parser,
     *  which joins into a 512-byte buffer. bstring::append truncates silently, so a key
     *  that does not fit here would register a handler under one name and dispatch it
     *  under another, with no diagnostic — check the length instead of losing it. */
    template <size_t S = 128, typename... ES>
    bstring<S> es_hash_str(ES... es) {
        // Each identifier fits in bstring64 (the parser caps one at 63 chars); only the
        // joined result needs the wider buffer.
        hvector<bstring64, 4> parts;
        (parts.push_back(es2str(es)), ...);
        auto cstr_compare = [](pcstr s1, pcstr s2) { return strcmp(s1, s2) < 0; };
        std::sort(parts.begin(), parts.end(), cstr_compare);
        size_t needed = parts.empty() ? 0 : parts.size() - 1;
        for (const auto& p : parts) {
            needed += strlen(p.c_str());
        }
        verify_no_crash_var(needed < S, "es_hash_str: key needs %d bytes, capacity %d", (int)needed, (int)S);
        bstring<S> result;
        bool first = true;
        for (const auto& p : parts) {
            if (!first) {
                result.append("+");
            }
            result.append(p.c_str());
            first = false;
        }
        return result;
    }
} // namespace js_helpers

template <typename T, typename... ES>
inline void js_event(const T& ev, ES... es) {
    js_event(ev, xstring(js_helpers::es_hash_str(es...)));
}

template <typename T>
inline void js_event(const T& ev) {
    type_name_holder<T> evname;
    js_event(ev, xstring(type_simplified_name(evname.value.data())));
}
