#pragma once

[[nodiscard]] int run_integral_tests();

extern bool g_test_signal_ready;

[[nodiscard]] bool test_log_contains(const char *marker);
