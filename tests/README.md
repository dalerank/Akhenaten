# Akhenaten integral tests

JS-driven unit tests run by the `--integraltests` mode.

## Running

```
./build/akhenaten --integraltests --no-logo --no-resource --window --size 800x600
```

`--window --size 800x600` keeps `screen_width`/`screen_height` stable so input-simulation tests can rely on fixed pixel coordinates instead of recomputing them per machine.

The game starts normally (logo skipped, no Pharaoh data required), then iterates over the `*.js` files in this folder in alphabetical order. Each test drives the game and inspects the resulting log file. Process exit code is `0` if every test passed, `1` otherwise.

Results are appended to `akhenaten-log.txt` as lines of the form `[test:NAME] PASS` or `[test:NAME] FAIL: ...`, plus a final `[integraltests] N passed, M failed` summary.

## Writing a test

Each `*.js` file in this folder must define exactly two global functions:

```js
function run_test() {
    // Drive the game: trigger UI actions, advance time, etc.
    // MUST eventually cause __test_signal_ready() to be called, either
    // synchronously (call it right here) or asynchronously (register an
    // [es=event_advance_day] handler that calls it when a condition is met).
    __test_signal_ready();
}

function check_valid() {
    // Inspect the log and/or game state, return true on success.
    var log = __test_read_log_file();
    return log.indexOf('[test-marker] something') >= 0;
}
```

If `__test_signal_ready()` is never called the driver times out after ~10 seconds (600 frames at 60 fps) and the test is marked FAIL.

## Naming convention

- `NN_short_name.js` — the `NN_` prefix orders the run sequence.
- Files starting with `_` are ignored by the driver (use for shared helpers if needed in the future).
- The test's reported name in the log is the full file stem, e.g. `tests/01_main_menu.js` → `[test:01_main_menu] PASS`.

## Available native bindings

| Function | Returns | Purpose |
|----------|---------|---------|
| `__test_read_log_file()` | string | Whole contents of `akhenaten-log.txt` (BOM stripped) |
| `__test_signal_ready()` | undefined | Tell the C++ driver to stop pumping frames and call `check_valid()` |
| `__test_pump_frames(n)` | undefined | Advance the real game loop by `n` frames (capped at 240) — use to let UI/events settle between simulated input actions |
| `__test_mouse_click(x, y)` | undefined | Synthesize a left mouse click at screen pixel `(x, y)`. Internally moves the cursor, presses left, pumps frames, releases, pumps more — onclick handlers fire as in a real session |
| `__test_mouse_right_click(x, y)` | undefined | Same as above for the right button. Most autoconfig windows (`allow_rmb_goback: true`) close on right-click anywhere outside a control |
| `__test_run_console_command(line)` | undefined | Dispatch `line` through the in-game debug console parser, exactly as if the player had typed it at the `~` prompt and pressed Enter. Use this to test `[console_command=...]` handlers end-to-end instead of calling the underlying JS function directly |
| `__log_info_native(msg)` | undefined | Write `msg` to the log (use to leave context lines for FAIL diagnostics) |
| `__log_marker(tag)` | undefined | Write `tag` to the log; in `--integraltests` mode it is prefixed with `[test-marker] ` so tests can grep for it, in normal play it is a plain log line. Use this from window init handlers to opt the window into test observability |

There is no global window-init hook. Each window that wants to be observable
from a test writes its own `__log_marker("window_show:<name>")` line from
its own `[es=(<window>, init)]` handler in `src/scripts/ui_<window>.js`. See
e.g. `ui_player_selection.js`, `ui_records_window.js`, `ui_mods_window.js`
for the pattern. When you add a new test that asserts a window transition,
add the matching `__log_marker` line at the top of that window's init
handler — that way the marker is opted into per-window, lives next to the
code under test, and a broken script silently failing to run init() will
silently fail the test (which is what we want).

All other in-game JS APIs (`game`, `__game_*`, `emit`, etc.) are also available — the runner shares the same VM with the normal game session.

## Constraints

- One process, sequential. Tests share global state. The next test's `run_test` / `check_valid` definitions overwrite the previous test's, but any window stack / mods / event handlers accumulate.
- The log file is truncated each time the process starts.
- The driver requires `--no-logo --no-resource` to be hermetic; CI sets `SDL_VIDEODRIVER=dummy` for headless runs.
