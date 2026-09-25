# MuJS engine (forked)

The embedded ECMAScript engine. Vendored from MuJS, but **this is a fork that is
actively edited** — not read-only third-party code. Do not try to sync it with
upstream: the divergences below are deliberate and upstream has no equivalent.

The binding layer that sits on top of this lives in `src/js/` — see `src/js/CLAUDE.md`.
Migration status, the per-family procedure and the phase plan: `docs/mujs_cpp_migration.md`.

## Build

Sources are `.cpp` and compile straight into the main target via
`file(GLOB MUJS_FILES ${PROJECT_SOURCE_DIR}/src/mujs/*.cpp)` in the root `CMakeLists.txt`.

`src/mujs/CMakeLists.txt` is **dead**: nothing ever `add_subdirectory()`s it, it declares
`project(mujs C)`, and it globs `*.c` — a pattern that now matches nothing. Editing it
has no effect.

Adding a file here needs a CMake reconfigure first (the glob has no `CONFIGURE_DEPENDS`).

## Line endings: CRLF

Every file in this directory is CRLF. Line-wise `perl -i -pe` preserves it because it
never touches the line terminator. Slurp mode (`-0777`) does not: patterns need `\r?\n`
and replacement text needs an explicit `\r\n`, otherwise the file ends up mixed and the
diff becomes unreviewable.

## The C→C++ migration

Free functions `js_foo(js_State *J, ...)` are being moved to methods `js_State::foo(...)`,
one family per commit. No compatibility wrappers are left behind: the old function is
deleted and every call site is rewritten.

**The only record of what has been migrated is the `js_State` class body in `jsi.h`.**
There is no tracker file. Anything still declared in `mujs.h` is still a free function.

Mechanics (full version in `docs/mujs_cpp_migration.md`):

- Declarations move out of the public `mujs.h` into `js_State` in `jsi.h`. The bridge sees
  the class because `src/js/js_game.h` includes `mujs/jsi.h`.
- In definitions, the C-era macros give way to members: `STACK/TOP/BOT` → `stack/top/bot`,
  `CHECKSTACK` → `JCHECKSTACK`, `stackidx(J, idx)` → `stackidx(this, idx)`.
- Watch for prefix traps when listing a family — `js_isarray` and `js_isarrayindex` are
  unrelated despite the name.
- The leftover grep must come back empty **including headers**: calls hide inside macro
  bodies (`src/js/js_defines.h`).

## Invariant: no destructors across `js_throw`

`js_throw()` unwinds with `longjmp`, which does not run destructors for the frames it
jumps over. Engine locals must stay trivially destructible — no `std::string`, no
`std::vector`, no RAII guard, nothing owning a resource. Allocate with `js_malloc` /
`js_frame_alloc` and release on the `js_try` error path instead.

`js_Object` is held to this by a `static_assert(std::is_trivially_destructible<js_Object>)`
in `jsvalue.h`: frame-arena objects are released wholesale without destruction, so a
member with a non-trivial destructor would leak silently for every ephemeral object.

## Divergences from stock MuJS

### Interned strings are the project's `xstring`
`js_StringNode` is `xstring_value*` (`jsstring.h`), interned through `js_intern`
(`jsintern.cpp`) — not MuJS's own string table. Property names, literals and identifiers
are all node pointers, so compare with `js_stringnode_cmp` and read with
`js_strnode_cstr`, never `strcmp` on the node itself.

### Extra value types
| Type | Backing | Purpose |
|------|---------|---------|
| `JS_CVEC2I` | `u.vec2`, `jsvec2i.cpp` | Integer 2D point with virtual `x`/`y` slots |
| `JS_CPTR` | raw native pointer | Script reads/writes a bound native field in place (`js_State::bind_global` / `bind_property`, slot from `js_cptr_type_of`) |
| `JS_CPTROFF` | `(char*)receiver->cobj_ptr + off` | Field of a native struct; reads yield `undefined` and writes no-op when `cobj_ptr` is null |

### Frame-zone arena
`js_enter_frame_zone` / `js_leave_frame_zone` (RAII: `struct js_frame_zone`). While
`frame_zone_depth > 0`, ephemeral objects, properties and iterators are taken from
`frame_alloc` and dropped wholesale at the end of the frame instead of being collected.
Added to stop per-frame GC hitching in draw paths (empire map). This is the reason for the
trivially-destructible rule above.

### `[es=(a, b)]` modifier tuples
Parsed by `parse_modifier_tuple_value` in `jsparse.cpp`: identifiers are sorted
lexicographically and joined with `+` into one interned key. Limits: 16 parts, 63 chars
per part, 128 chars joined.

**These limits must stay in step with `js_helpers::es_hash_str` / `es2str_checked` in
`src/js/js_game.h`.** If the two sides compute a key differently, the handler registers
under one string and dispatch looks up another — it never fires, silently. Both sides
therefore abort on overflow rather than truncate. Covered by `src/js/js_self_tests.cpp`.

### Debug hook
`debug_hook` fires on every `OP_LINE`; the DAP server in `src/js/js_debugger.cpp` consumes
it. Both hook fields are zero-initialised by `js_newstate`.

### Profiler zones
`OZZY_PROFILER_FUNCTION` / `OZZY_PROFILER_SECTION` (the project's Tracy wrapper) are
present in `jsrun.cpp`, `jsgc.cpp`, `jsproperty.cpp`, `jsintern.cpp`, `jsvalue.cpp`.
Property access zones are labelled with the property name.

## Verification

Build with a real exit code — piping through `tail`/`head` returns the pipe's status, so a
broken build reads as success:
```
cmake --build --preset win-msvc-relwithdebinfo-vs2022 > log 2>&1; echo $?
```
Then run the integral suite (see the root `CLAUDE.md`). Engine-level invariants that the
suite cannot reach live in `src/js/js_self_tests.cpp`.
