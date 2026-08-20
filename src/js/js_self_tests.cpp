#include "js_self_tests.h"

#include "core/core.h"
#include "core/log.h"
#include "core/variant.h"
#include "mujs/jsi.h"
#include "mujs/jsvalue.h"
#include "mujs/mujs.h"
#include "js/js.h"
#include "js/js_game.h"
#include "regexp.h"

#include <cstring>

namespace {

static uint8_t mujs_self_test_u8_a;
static uint8_t mujs_self_test_u8_b;

/** Registers globals.__mujs_self_test_cptr with CPTR u8_a / u8_b (mirrors city.kingdome bound fields). */
static void mujs_self_test_register_cptr_holder(js_State *J)
{
    mujs_self_test_u8_a = 0;
    mujs_self_test_u8_b = 0;
    js_newobject(J);
    js_register_bound_uint8_property(J, js_intern("u8_a"), &mujs_self_test_u8_a);
    js_register_bound_uint8_property(J, js_intern("u8_b"), &mujs_self_test_u8_b);
    js_setglobal(J, "__mujs_self_test_cptr");
}

/** One regexp check: first match, capture group @a cap must equal @a expected (byte-wise). */
static bool mujs_self_test_regexp(pcstr id, pcstr pattern, pcstr subject, int cap, pcstr expected)
{
    const char *error = nullptr;
    Reprog *prog = regcomp(pattern, 0, &error);
    verify_no_crash_var(prog, "mujs_self_test_regexp %s: regcomp failed: %s", id, error ? error : "?");
    if (!prog)
        return false;
    Resub m;
    memset(&m, 0, sizeof(m));
    int err = regexec(prog, subject, &m, 0);
    regfree(prog);
    verify_no_crash_var(err == 0, "mujs_self_test_regexp %s: no match (pattern=%s subject=%s)", id, pattern, subject);
    if (err)
        return false;
    verify_no_crash_var(cap >= 0 && cap < REG_MAXSUB && m.sub[cap].sp, "mujs_self_test_regexp %s: invalid capture %d", id, cap);
    if (cap < 0 || cap >= REG_MAXSUB || !m.sub[cap].sp)
        return false;
    const char *sp = m.sub[cap].sp;
    const char *ep = m.sub[cap].ep;
    size_t n = (size_t)(ep - sp);
    size_t exp_len = strlen(expected);
    const bool capture_ok = (n == exp_len && (n == 0 || memcmp(sp, expected, n) == 0));
    verify_no_crash_var(capture_ok, "mujs_self_test_regexp %s: capture %d mismatch (got len %zu, want %zu)", id, cap, n, exp_len);
    return capture_ok;
}

static bool mujs_self_test_js(js_State *J, pcstr id, pcstr source)
{
    if (js_try(J)) {
        // js_throw already popped the try frame — do not js_endtry here.
        xstring msg = js_toxstring(J, -1);
        verify_no_crash_var(false, "mujs_self_test_js %s: exception: %s", id, msg.empty() ? "?" : msg.c_str());
        js_pop(J, 1);
        return false;
    }
    js_loadeval(J, "[mujs_self_tests]", source);
    js_pushglobal(J);
    J->call(0);
    const int ok = js_toboolean(J, -1);
    js_pop(J, 1);
    js_endtry(J);
    verify_no_crash_var(ok, "mujs_self_test_js %s: falsy result", id);
    return ok != 0;
}

/** Multiple [es=(section, name), es=(…)] on one function must register under each hash. */
static bool mujs_self_test_multi_es_modifiers(js_State *J)
{
    static const char *k_probe =
        "__mujs_multi_es_hits = 0;\n"
        "[es=(win_b, ping), es=(win_a, ping)]\n"
        "function __mujs_multi_es_probe(ev) { __mujs_multi_es_hits = (__mujs_multi_es_hits|0) + 1; }\n"
        "true";

    if (!mujs_self_test_js(J, "multi_es_define", k_probe))
        return false;

    const bstring64 hash_a = js_helpers::es_hash_str("win_a", "ping");
    const bstring64 hash_b = js_helpers::es_hash_str("win_b", "ping");
    verify_no_crash_var(hash_a == "ping+win_a", "multi_es: hash_a");
    verify_no_crash_var(hash_b == "ping+win_b", "multi_es: hash_b");
    if (hash_a != "ping+win_a" || hash_b != "ping+win_b")
        return false;

    js_getglobal(J, "__mujs_multi_es_probe");
    verify_no_crash_var(J->iscallable(-1), "multi_es: probe is callable");
    const int has_es = js_hasmodifier(J, -1, js_intern("es"));
    js_pop(J, 1);
    verify_no_crash_var(has_es, "multi_es: probe missing es modifier");
    if (!has_es)
        return false;

    js_register_game_handlers({});
    verify_no_crash_var(js_has_event_handlers(xstring(hash_a.c_str())), "multi_es: no handler for %s", hash_a.c_str());
    verify_no_crash_var(js_has_event_handlers(xstring(hash_b.c_str())), "multi_es: no handler for %s", hash_b.c_str());
    if (!js_has_event_handlers(xstring(hash_a.c_str())) || !js_has_event_handlers(xstring(hash_b.c_str())))
        return false;

    bvariant_map empty;
    js_call_event_handlers(xstring(hash_a.c_str()), empty);
    js_call_event_handlers(xstring(hash_b.c_str()), empty);

    js_getglobal(J, "__mujs_multi_es_hits");
    const int hits = js_tointeger(J, -1);
    js_pop(J, 1);
    verify_no_crash_var(hits == 2, "multi_es: expected 2 calls, got %d", hits);
    return hits == 2;
}

} // namespace

void mujs_run_self_tests(js_State *J)
{
    mujs_self_test_register_cptr_holder(J);

    mujs_self_test_regexp("negated_brace_cap1", R"(\$\{([^}]+)\})", "${stored} more", 1, "stored");
    mujs_self_test_regexp("negated_brace_cap1_twice_prefix", R"(\$\{([^}]+)\})", "${a} ${b} x", 1, "a");
    mujs_self_test_js(J, "regexp_replace_capture", "(function(){ return '${z}'.replace(/\\$\\{([^}]+)\\}/, function(m, g) { return g; }) === 'z'; })()");
    mujs_self_test_js(J, "regexp_replace_global_capture", "(function(){ return '${a} ${b}'.replace(/\\$\\{([^}]+)\\}/g, function(m, g) { return g; }) === 'a b'; })()");
    /* Two consecutive OP_SETPROP_S writes on one object; stack must stay two-deep until rot2pop1 (kingdome salary_rank + salary_amount). */
    mujs_self_test_js(J, "c_uint8_sequential_member_assign",
        "(function(){ function two_writes(){ __mujs_self_test_cptr.u8_a = 7; var x = 42; "
        "__mujs_self_test_cptr.u8_b = x; } two_writes(); "
        "return __mujs_self_test_cptr.u8_a === 7 && __mujs_self_test_cptr.u8_b === 42; })()");
    mujs_self_test_multi_es_modifiers(J);

    {
        js_frame_zone zone(J);
        js_newobject(J);
        js_Object *ephem = J->toobject(-1);
        verify_no_crash_var(ephem && ephem->ephemeral, "frame_zone_ephemeral_flag");
        js_pop(J, 1);
    }

    {
        js_frame_zone zone(J);
        const unsigned before = js_frame_escape_count(J);
        if (js_try(J)) {
            // js_throw already popped the try frame — do not js_endtry here.
            js_pop(J, 1);
            verify_no_crash_var(js_frame_escape_count(J) > before,
                "frame_zone_escape_hard: expected escape count bump");
        } else {
            js_newobject(J);
            js_setglobal(J, "__mujs_frame_zone_escape_probe");
            js_endtry(J);
            verify_no_crash_var(false, "frame_zone_escape_hard: expected js_error on heap store");
        }
    }
}
