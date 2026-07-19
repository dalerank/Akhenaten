# Figure Subsystem

Framework for all moving entities in the game. Owns base class, movement, routing, AI state machine, formations, and combat.
Concrete figure types live in `../figuretype/`.

## Key Files

| File | Purpose |
|------|---------|
| `figure.h / .cpp` | Instance data: position, state, routing, home/dest buildings, animation |
| `figure_impl.h / .cpp` | Abstract base for figure behavior (virtual hooks) |
| `figure_type.h` | Enum of 177+ figure types |
| `figure_static_params.h` | Immutable per-type config: animations, sounds, terrain usage, combat stats |
| `action.h / .cpp` | Action state dispatch, movement primitives (goto, roam, return) |
| `formation.h / .cpp` | Group movement, military formations, morale |
| `combat.h` | Attack/damage mechanics |
| `movement.h / route.h` | Pathfinding and route following |
| `service.h` | Service provision framework |

## figure/ vs figuretype/

| | `figure/` | `figuretype/` |
|--|-----------|---------------|
| Role | Framework/contracts | Concrete implementations |
| Modify when | Changing movement/routing/AI base | Adding new unit type |
| Base types | `figure`, `figure_impl` | `figure_worker`, `figure_soldier`, `figure_enemy`, `figure_animal` |

## AI State Machine

```
figure::action_perform()
  ├─ figure_before_action()   // one-time init per action (virtual)
  ├─ figure_roaming_action()  // shared roaming/fleeing logic (virtual)
  └─ figure_action()          // type-specific main logic (virtual)
```

- `action_state` (uint16_t) drives the state machine for each type
- `advance_action(next_state)` transitions and resets progress counters
- Common primitives: `do_gotobuilding()`, `do_returnhome()`, `do_roam()`, `do_enterbuilding()`, `do_exitbuilding()`

## Adding a New Figure Type

1. Create `figuretype/figure_mytype.h/.cpp` inheriting from `figure_worker`, `figure_soldier`, etc.
2. `FIGURE_METAINFO(FIGURE_MYTYPE, figure_mytype)` sets `TYPE`/`CLSID` — but it does **not**
   register the type. Registration into the `figure_impl::acquire` ctor loop happens via
   `REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_mytype)` in the `.cpp` (its global
   `model_t<T>` constructor adds the ctor). **Omit it and the type silently falls back to a
   base `figure_impl`** — `dcast_*()` returns null and debug builds hit `assert(false)` in
   `figure_impl::acquire`.
3. Implement `figure_action()` with action state transitions.
4. Define nested `static_params` and `runtime_data_t` (max 40 bytes, `static_assert` enforced).
   A subclass may add **no data members** — `static_assert(sizeof(T) == sizeof(figure_impl))`
   enforces this; all mutable state lives in `runtime_data` (`FIGURE_RUNTIME_DATA_T`).
5. Static params bind **by class-name string** (`CLSID`): class `figure_mytype` ⇄ config
   `figure_mytype = { ... }` in `src/scripts/figures.js` / `enemies.js`. Animations, sounds,
   and combat live in the `figure_static_params` base (parsed generically); `ANK_CONFIG_STRUCT`
   lists only the **extra** fields. New `.cpp` files need a CMake reconfigure (see root
   `CLAUDE.md`). Reference: `figure_enemy_chariot.{h,cpp}` (12 leaves, shared base, one config
   per class); regression pattern: `tests/39_enemy_chariot_registered.js`.

## Cross-Subsystem Connections

- **`building/`** — `home_building_id`, `destination_building_id`; buildings spawn and track figures via slots
- **`grid/`** — `tile` (current pos), routing path ID, terrain traversal mode (ROADS, ENEMY, WATER, AMPHIBIA)
- **`city/`** — figures pooled in city (MAX_FIGURES = 2000); `faction_id` (1=player, 0=enemy); formation_id

## Formations (Military)

- Up to 6 formations per city, max 16 figures per formation
- Morale system: tracks months away from home
- Enemy formations: pre-built with nationality + unit-type variance

## Invariants

- Figure state: ALIVE, DYING, DEAD (NONE = unused slot)
- Home building must be valid — figures disappear if home is destroyed
- Max 40 bytes in `runtime_data` — checked by `static_assert`
- Animation context must always be set (defaults to walk animation)
- Never use `static_cast` for downcasts — use factory/dcast equivalents
