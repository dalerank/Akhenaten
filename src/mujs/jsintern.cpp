#include "jsi.h"

#include "core/profiler.h"

js_StringNode js_intern(pcstr s) {
    OZZY_PROFILER_FUNCTION();
    if (!s) {
        return nullptr;
    }

    return (js_StringNode)(xstring(s)._get());
}
