#pragma once

// Every native registered from a TU that includes this header first goes to
// config::TestFunctionIterator and is exposed to JS only under --integraltests.
#ifdef ANK_JS_FUNCTION_REGISTRY
#error "js/test/js_test_common.h must be the first include of a test-binding file"
#endif
#define ANK_JS_FUNCTION_REGISTRY config::TestFunctionIterator

#include "js/js.h"
#include "js/js_defines.h"
#include "js/js_game.h"
#include "mujs/mujs.h"

// Bindings that other test-binding files also call directly.
int __test_count_figures(int type);
