#pragma once

#include "core/hvector.h"
#include "core/xstring.h"

[[nodiscard]] int run_integral_tests();

// All tests/*.js paths (no --integraltest-only filter). Used by the options window picker.
[[nodiscard]] hvector<xstring, 16> list_integral_test_files();

extern bool g_test_signal_ready;

// Searches the log from the last test_log_mark_test_start(), so one test's markers or errors
// cannot pass or fail a later test.
[[nodiscard]] bool test_log_contains(const char *marker);
void test_log_mark_test_start();

// Drop city/editor session + scenario events and return to main menu so the next
// test's test_ensure_city_session() reloads a fresh map.
void test_reset_session_between_tests();
