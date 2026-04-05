#include "js_self_tests.h"

#include "core/core.h"
#include "core/log.h"
#include "mujs/jsi.h"
#include "mujs/jsvalue.h"
#include "mujs/mujs.h"
#include "regexp.h"

#include <cstring>

namespace {

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
        pcstr msg = js_strnode_cstr(js_tostring(J, -1));
        verify_no_crash_var(false, "mujs_self_test_js %s: exception: %s", id, msg ? msg : "?");
        js_pop(J, 1);
        js_endtry(J);
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

} // namespace

void mujs_run_self_tests(js_State *J)
{
    mujs_self_test_regexp("negated_brace_cap1", R"(\$\{([^}]+)\})", "${stored} more", 1, "stored");
    mujs_self_test_regexp("negated_brace_cap1_twice_prefix", R"(\$\{([^}]+)\})", "${a} ${b} x", 1, "a");
    mujs_self_test_js(J, "regexp_replace_capture", "(function(){ return '${z}'.replace(/\\$\\{([^}]+)\\}/, function(m, g) { return g; }) === 'z'; })()");
    mujs_self_test_js(J, "regexp_replace_global_capture", "(function(){ return '${a} ${b}'.replace(/\\$\\{([^}]+)\\}/g, function(m, g) { return g; }) === 'a b'; })()");
}
