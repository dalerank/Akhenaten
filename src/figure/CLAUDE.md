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
2. Use `FIGURE_METAINFO(FIGURE_MYTYPE, figure_mytype)` macro for registration
3. Implement `figure_action()` with action state transitions
4. Define nested `static_params` and `runtime_data_t` (max 40 bytes, `static_assert` enforced)
5. Implement animations and sounds in config

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
