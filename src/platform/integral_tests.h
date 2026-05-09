#pragma once

/** Runs built-in checks that do not require Pharaoh game data or asset archives.
 * @return 0 if all checks passed, non-zero otherwise */
[[nodiscard]] int run_integral_tests();
